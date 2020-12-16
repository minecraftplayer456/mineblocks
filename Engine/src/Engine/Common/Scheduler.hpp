#pragma once

#include <thread>
#include <mutex>
#include <atomic>

namespace Engine{
    class Scheduler;

    enum class TaskPriority{
        Highest,
        High,
        Normal,
        Low,
        Lowest
    };

    class Task {
        friend Scheduler;

      public:
        virtual ~Task() = default;

        virtual void Run(uint32_t threadId) = 0;

      private:
        bool completed = false;
    };

    enum class ThreadState{
        NONE,
        NOT_LAUNCHED,
        RUNNING,
        WAIT_NEW_TASK,
        WAIT_TASK_COMPLETE,
        STOPPED
    };

    struct ThreadData{
      public:
        std::atomic<ThreadState> State = ThreadState::NONE;
    };

    struct ThreadArgs{
      public:
        uint32_t ThreadId;
        Scheduler* Scheduler;
    };

    class Scheduler {
      public:
        ~Scheduler();

        void Initialize();
        void Cleanup();

        void AddTaskToQueue(Task* task);

        void WaitForTask(Task* task);

      private:
        std::atomic<bool> running;

        std::mutex mutex;

        std::vector<std::thread> threadPool;
        std::queue<Task*> taskQueue;

        static void TaskingThreadFunction(const ThreadArgs& args);
    };
};