#pragma once
#include "Minty/Data/Map.h"
#include "Minty/Data/Pair.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Queue.h"
#include "Minty/Data/Vector.h"
#include <thread>
#include <condition_variable>
#include <mutex>
#include <functional>

namespace Minty
{
	using Job = std::function<void()>;
	using ParallelJob = std::function<void(Size)>;

	/// <summary>
	/// Arguments for creating a JobManager.
	/// </summary>
	struct JobManagerBuilder
	{
		/// <summary>
		/// The number of threads to use.
		/// </summary>
		Size threadCount = 4;
	};

	/// <summary>
	/// Handles batching and executing Jobs.
	/// </summary>
	class JobManager
	{
#pragma region Classes

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

#pragma region Variables

	private:
		Allocator m_allocator;
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
		Queue<Pair<Job, Handle>> m_queue;
		std::mutex m_queueMutex;
		// the condition variable used to notify the threads
		std::condition_variable m_condition;
		// if the threads should stop running
		Bool m_stop;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new JobManager.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <param name="allocator">The Allocator to use.</param>
		JobManager(JobManagerBuilder const& builder, Allocator const allocator = Allocator::Default);

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
		/// <summary>
		/// Schedules the given Job to run.
		/// </summary>
		/// <param name="action">The action to run.</param>
		/// <returns>A Handle to the new Job.</returns>
		Handle schedule(Job const action)
		{
			return schedule(action, Vector<Handle>());
		}

		/// <summary>
		/// Schedule the given Job to run after the given dependency has completed.
		/// </summary>
		/// <param name="action">The action to run.</param>
		/// <param name="dependency">The Job to wait on.</param>
		/// <returns>A Handle to the new Job.</returns>
		Handle schedule(Job const action, Handle const dependency)
		{
			return schedule(action, Vector<Handle>({dependency}));
		}

		/// <summary>
		/// Schedule the given Job to run after all the given dependencies have completed.
		/// </summary>
		/// <param name="action">The action to run.</param>
		/// <param name="dependencies">The Jobs to wait on.</param>
		/// <returns>A Handle to the new Job.</returns>
		Handle schedule(Job const action, Vector<Handle> const& dependencies);

		/// <summary>
		/// Schedules the given action to run in parallel count times. Each action will be given an index in the range of [0, count).
		/// </summary>
		/// <param name="count">The number of actions to run.</param>
		/// <param name="action">The base action to run.</param>
		/// <returns>A Handle to the new Job.</returns>
		Handle schedule_parallel(ParallelJob const action, Size const count)
		{
			return schedule_parallel(action, count, Vector<Handle>());
		}

		/// <summary>
		/// Schedules the given action to run in parallel count times, after the given dependency has been completed. Each action will be given an index in the range of [0, count).
		/// </summary>
		/// <param name="count">The number of actions to run.</param>
		/// <param name="action">The base action to run.</param>
		/// <param name="dependency">The Job to wait on.</param>
		/// <returns>A Handle to the new Job.</returns>
		Handle schedule_parallel(ParallelJob const action, Size const count, Handle const dependency)
		{
			return schedule_parallel(action, count, Vector<Handle>({dependency}));
		}

		/// <summary>
		/// Schedules the given action to run in parallel count times, after all the given dependencies have been completed. Each action will be given an index in the range of [0, count).
		/// </summary>
		/// <param name="count">The number of actions to run.</param>
		/// <param name="action">The base action to run.</param>
		/// <param name="dependencies">The Jobs to wait on.</param>
		/// <returns>A Handle to the new Job.</returns>
		Handle schedule_parallel(ParallelJob const action, Size const count, Vector<Handle> const& dependencies);

		/// <summary>
		/// Checks if the Job with the given handle has completed. Assumes the Handle belongs to a Job which was previously scheduled.
		/// </summary>
		/// <param name="handle">The Handle to check.</param>
		/// <returns>True if the Job no longer exists.</returns>
		Bool is_complete(Handle const handle) const { return !m_jobs.contains(handle); }

		/// <summary>
		/// Waits for the Job with the given handle to complete. Assumes the Handle belongs to a Job which was previously scheduled.
		/// </summary>
		/// <param name="handle">The Handle of the Job to wait for.</param>
		void wait(Handle const handle);

		/// <summary>
		/// Waits for all of the given Handles to complete. Assumes the Handles belong to Jobs which were previously scheduled.
		/// </summary>
		/// <param name="handles">The Handles of the Jobs to wait for.</param>
		void wait(Vector<Handle> const& handles);

#pragma endregion

	};
}