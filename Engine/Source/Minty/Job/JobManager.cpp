#include "pch.h"
#include "JobManager.h"
#include "Minty/Application/Application.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Job/JobManagerInfo.h"
#include "Minty/Memory/DefaultAllocator.h"

using namespace Minty;

Minty::JobManager::JobManager(JobManagerInfo const &info)
	: m_threads(), m_nextHandle(0), m_jobs(), m_queue(), m_queueMutex(), m_stop(false)
{
	MINTY_ASSERT(info.threadCount > 0, ErrorCode::Argument_ExpectedNonZero);

	// create threads
	m_threads.reserve(info.threadCount);

	for (Size i = 0; i < m_threads.get_capacity(); ++i)
	{
		m_threads.add(std::thread([this]()
								  { worker_thread(); }));
	}
}

Minty::JobManager::~JobManager()
{
	// mark as stopped
	{
		std::unique_lock<std::mutex> lock(m_queueMutex);
		m_stop = true;
	}

	// notify all threads
	m_condition.notify_all();

	// wait for threads to finish
	for (auto &thread : m_threads)
	{
		thread.join();
	}
}

void Minty::JobManager::worker_thread()
{
	Tuple<Job, Handle> pair = {[]() {}, 0};
	JobData *jobData;
	Bool complete;

	while (true)
	{
		// get next job
		{
			// wait until stopping, or until there is a job
			std::unique_lock lock(m_queueMutex);
			m_condition.wait(lock, [this]()
							 { return m_stop || !m_queue.is_empty(); });

			// if stopping, exit
			if (m_stop)
				return;

			// get the next job
			pair = std::move(m_queue.pop());
		}

		// run the job
		pair.get_first()();

		// get the job data
		{
			std::unique_lock lock(m_jobsMutex);
			jobData = m_jobs.at(pair.get_second());
		}

		// decrement the job count
		{
			std::unique_lock lock(jobData->mutex);
			--jobData->jobCount;
			complete = jobData->jobCount == 0;
		}

		if (complete)
		{
			{
				std::unique_lock lock(jobData->mutex);

				// notify dependents when complete
				for (Handle dependent : jobData->dependents)
				{
					// get dependent job data
					JobData *dependentData;
					{
						std::unique_lock lock(m_jobsMutex);
						dependentData = m_jobs.at(dependent);
					}

					{
						std::unique_lock lock(dependentData->mutex);

						// decrement dependency count
						--dependentData->dependencyCount;

						// if dependency count is zero, it can be scheduled
						if (dependentData->dependencyCount == 0)
						{
							schedule_batch(dependent);
						}
					}
				}
			}

			// remove this job's resources
			{
				std::unique_lock lock(m_jobsMutex);
				m_jobs.remove(pair.get_second());
			}
			DefaultAllocator<JobData>().destruct(jobData);
		}
	}
}

Handle Minty::JobManager::create_job(Vector<Job> const &batch, Vector<Handle> const &dependencies)
{
	Handle handle = m_nextHandle++;
	JobData *jobData = DefaultAllocator<JobData>().construct(dependencies.get_size(), batch.get_size());
	{
		// add new job
		std::unique_lock lock(m_jobsMutex);
		MINTY_ASSERT_F(!m_jobs.contains(handle), ErrorCode::Threading_HandleAlreadyExists, handle);
		m_jobs.add(handle, jobData);

		// add this job as dependents to the dependencies
		for (Handle dependency : dependencies)
		{
			MINTY_ASSERT(handle != dependency, ErrorCode::Threading_CyclicDependency);

			auto it = m_jobs.find(dependency);

			// if job with handle not found, assume it is already completed
			if (it == m_jobs.end())
			{
				// decrement dependency count
				--jobData->dependencyCount;
				continue;
			}

			// dependency is not complete, so add this job as a dependent
			JobData *dependencyData = m_jobs[dependency];
			{
				std::unique_lock lock(dependencyData->mutex);
				dependencyData->dependents.add(handle);
			}
		}
	}

	// if no dependencies, schedule now, otherwise, schedule later
	if (jobData->dependencyCount == 0)
	{
		schedule_batch(handle, batch);
	}
	else
	{
		create_batch(handle, batch);
	}

	return handle;
}

void Minty::JobManager::create_batch(Handle const handle, Vector<Job> const &batch)
{
	{
		std::unique_lock lock(m_batchesMutex);
		MINTY_ASSERT_F(!m_batches.contains(handle), ErrorCode::Argument_KeyAlreadyExists, handle);
		m_batches.add(handle, batch);
	}
}

void Minty::JobManager::schedule_batch(Handle const handle, Vector<Job> const &batch)
{
	// add each action to queue and start it
	for (Job const &job : batch)
	{
		{
			std::unique_lock lock(m_queueMutex);
			m_queue.push({job, handle});
		}
		m_condition.notify_one();
	}
}

void Minty::JobManager::schedule_batch(Handle const handle)
{
	// get the batch
	Vector<Job> batch;
	{
		std::unique_lock lock(m_batchesMutex);
		batch = std::move(m_batches.at(handle));
		m_batches.remove(handle);
	}

	// schedule it
	schedule_batch(handle, batch);
}

Handle Minty::JobManager::schedule(Job const action, Vector<Handle> const &dependencies)
{
	// create batch
	Vector<Job> batch = {action};

	return create_job(batch, dependencies);
}

Handle Minty::JobManager::schedule_parallel(ParallelJob const action, Size const count, Vector<Handle> const &dependencies)
{
	// create batch
	Vector<Job> batch(count);
	for (Size i = 0; i < count; ++i)
	{
		batch.add(std::move([action, i]()
							{ action(i); }));
	}

	// create job data
	return create_job(batch, dependencies);
}

void Minty::JobManager::wait(Handle const handle)
{
	Bool waiting = false;
	do
	{
		if (waiting)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		{
			std::unique_lock lock(m_jobsMutex);
			waiting = m_jobs.contains(handle);
		}
	} while (waiting);
}

void Minty::JobManager::wait(Vector<Handle> const &handles)
{
	// wait for each handle in order
	for (Handle handle : handles)
	{
		wait(handle);
	}
}

Unique<JobManager> Minty::JobManager::create(JobManagerInfo const &info)
{
	return Unique<JobManager>::create(info);
}

Unique<JobManager> Minty::JobManager::create()
{
	JobManagerInfo info{};
	return create(info);
}

Unique<JobManager> const& Minty::JobManager::get_instance()
{
	return Application::get_singleton().get_job_manager();
}

JobManager& Minty::JobManager::get_singleton()
{
	Unique<JobManager> const& instance = Application::get_singleton().get_job_manager();
	MINTY_ASSERT(instance, ErrorCode::Application_JobManagerNotInitialized);
	return *instance;
}