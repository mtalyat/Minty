#ifndef MINTY_JOB_JOBMANAGER_H
#define MINTY_JOB_JOBMANAGER_H

/**
 * @file JobManager.h
 * @brief Header file for the JobManager class.
 * @author Mitchell Talyat
 */

#include "Minty/Manager/Manager.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Queue.h"
#include "Minty/Data/Vector.h"
#include "Minty/Memory/DefaultAllocator.h"
#include <thread>
#include <condition_variable>
#include <mutex>

namespace Minty
{
	struct JobManagerInfo;

	/**
	 * @brief Handles batching and executing Jobs.
	 */
	class JobManager
		: public Manager
	{
#pragma region Types

	private:
		struct JobData
		{
			// the number of dependencies that need to be completed before this function can run
			Size dependencyCount = 0;
			// the number of functions left to complete running
			Size jobCount = 0;
			// a list of functions to run after this one is complete
			Vector<Handle> dependents = {};
			// a mutex to protect the data
			std::mutex mutex = {};
		};

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates a new JobManager.
		 * @param info The arguments.
		 * @param allocator The Allocator to use.
		 */
		JobManager(JobManagerInfo const& info);

		~JobManager();

#pragma endregion

#pragma region Methods

	private:
		// the function used by each worker thread
		void worker_thread();

		// create job data
		Handle create_job(Vector<Job> const& batch, Vector<Handle> const& dependencies);

		// creates a batch of jobs to run later
		void create_batch(Handle const handle, Vector<Job> const& batch);

		// schedules a batch of jobs to run
		void schedule_batch(Handle const handle, Vector<Job> const& batch);

		// removes the batch from the batches list, and schedules it to run
		void schedule_batch(Handle const handle);

	public:
		/**
		 * @brief Schedules the given Job to run.
		 * @param action The action to run.
		 * @return A Handle to the new Job.
		 */
		Handle schedule(Job const action)
		{
			return schedule(action, Vector<Handle>());
		}

		/**
		 * @brief Schedule the given Job to run after the given dependency has completed.
		 * @param action The action to run.
		 * @param dependency The Job to wait on.
		 * @return A Handle to the new Job.
		 */
		Handle schedule(Job const action, Handle const dependency)
		{
			return schedule(action, Vector<Handle>({dependency}));
		}

		/**
		 * @brief Schedule the given Job to run after all the given dependencies have completed.
		 * @param action The action to run.
		 * @param dependencies The Jobs to wait on.
		 * @return A Handle to the new Job.
		 */
		Handle schedule(Job const action, Vector<Handle> const& dependencies);

		/**
		 * @brief Schedules the given action to run in parallel count times. Each action will be given an index in the range of [0, count).
		 * @param action The base action to run.
		 * @param count The number of actions to run.
		 * @return A Handle to the new Job.
		 */
		Handle schedule_parallel(ParallelJob const action, Size const count)
		{
			return schedule_parallel(action, count, Vector<Handle>());
		}

		/**
		 * @brief Schedules the given action to run in parallel count times, after the given dependency has been completed. Each action will be given an index in the range of [0, count).
		 * @param action The base action to run.
		 * @param count The number of actions to run.
		 * @param dependency The Job to wait on.
		 * @return A Handle to the new Job.
		 */
		Handle schedule_parallel(ParallelJob const action, Size const count, Handle const dependency)
		{
			return schedule_parallel(action, count, Vector<Handle>({dependency}));
		}

		/**
		 * @brief Schedules the given action to run in parallel count times, after all the given dependencies have been completed. Each action will be given an index in the range of [0, count).
		 * @param action The base action to run.
		 * @param count The number of actions to run.
		 * @param dependencies The Jobs to wait on.
		 * @return A Handle to the new Job.
		 */
		Handle schedule_parallel(ParallelJob const action, Size const count, Vector<Handle> const& dependencies);

		/**
		 * @brief Checks if the Job with the given handle has completed. Assumes the Handle belongs to a Job which was previously scheduled.
		 * @param handle The Handle to check.
		 * @return True if the Job no longer exists.
		 */
		Bool is_complete(Handle const handle) const { return !m_jobs.contains(handle); }

		/**
		 * @brief Waits for the Job with the given handle to complete. Assumes the Handle belongs to a Job which was previously scheduled.
		 * @param handle The Handle of the Job to wait for.
		 */
		void wait(Handle const handle);

		/**
		 * @brief Waits for all of the given Handles to complete. Assumes the Handles belong to Jobs which were previously scheduled.
		 * @param handles The Handles of the Jobs to wait for.
		 */
		void wait(Vector<Handle> const& handles);

		/**
		 * @brief Creates a new JobManager.
		 * @param info The arguments.
		 * @return A JobManager Owner.
		 */
		static Unique<JobManager> create(JobManagerInfo const& info);

		/**
		 * @brief Creates a new JobManager with default settings.
		 * @return A JobManager Owner.
		 */
		static Unique<JobManager> create();

		/**
		 * @brief Gets the active Context's JobManager.
		 * @return The JobManager.
		 */
		static Unique<JobManager> const& get_instance();

		/**
		 * @brief Gets the active Context's JobManager.
		 * @return A reference to the JobManager.
		 */
		static JobManager& get_singleton();

#pragma endregion

#pragma region Variables

	private:
		// the threads used to run the jobs
		Vector<std::thread> m_threads;
		// the next handle to use
		Handle m_nextHandle;
		// the jobs that are currently running, or waiting to be ran
		Map<Handle, JobData*> m_jobs;
		std::mutex m_jobsMutex;
		// the batches of actions that are waiting to be ran
		Map<Handle, Vector<Job>> m_batches;
		std::mutex m_batchesMutex;
		// the queue of actions to run
		Queue<Tuple<Job, Handle>> m_queue;
		std::mutex m_queueMutex;
		// the condition variable used to notify the threads
		std::condition_variable m_condition;
		// if the threads should stop running
		Bool m_stop;
		DefaultAllocator m_jobDataAllocator;

#pragma endregion
	};
}

#endif // MINTY_JOB_JOBMANAGER_H