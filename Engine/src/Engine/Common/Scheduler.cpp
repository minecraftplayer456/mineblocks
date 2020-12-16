#include "Scheduler.hpp"

namespace Engine{
    Scheduler::~Scheduler()
    {
        Cleanup();
    }

    void Scheduler::Initialize()
    {
        if(running){
            Cleanup();
        }

        unsigned int threadAmount = std::thread::hardware_concurrency();

        if(threadAmount != 0){
            threadAmount = threadAmount - 1;
        }else{
            ENGINE_CORE_DEBUG("Could not gather hardware concurrency. Use 2 threads");
            threadAmount = 2;
        }

        ENGINE_CORE_DEBUG("Initializing scheduler with {} threads in the thread pool", threadAmount);

        running = true;

        for(uint32_t threadId = 0; threadId < threadAmount; threadId++){
            ThreadArgs args {threadId, this};
            std::thread thread(TaskingThreadFunction, args);
            threadPool.push_back(std::move(thread));
        }
    }

    void Scheduler::Cleanup()
    {
        running = false;

        for(std::thread& thread : threadPool){
            thread.join();
        }

        threadPool.clear();

        for(int i = 0; i < taskQueue.size(); i++){
            taskQueue.pop();
        }
    }

    void Scheduler::AddTaskToQueue(Task* task)
    {
        std::lock_guard<std::mutex> lg(mutex);
        task->completed = false;
        taskQueue.push(task);
    }

    void Scheduler::WaitForTask(Task* task)
    {
        while(!task->completed){

        }
    }

    void Scheduler::TaskingThreadFunction(const ThreadArgs& args)
    {
        Scheduler* scheduler = args.Scheduler;
        while(scheduler->running.load(std::memory_order_relaxed)){
            std::unique_lock<std::mutex> lg(scheduler->mutex);
            if(!scheduler->taskQueue.empty()){
                Task* task = scheduler->taskQueue.front();
                scheduler->taskQueue.pop();
                lg.unlock();
                task->Run(args.ThreadId);
                task->completed = true;
            }
        }
    }
};