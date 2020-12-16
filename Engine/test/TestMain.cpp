#include "Engine/Common/Scheduler.hpp"

class TestTask : public Engine::Task{
    void Run(uint32_t threadId) override{
        ENGINE_CORE_INFO("Hi! id: {}", threadId);
    }
};

int main(){
    Engine::Log::Initialize();

    Engine::Scheduler scheduler;
    scheduler.Initialize();

    TestTask task;
    TestTask task2;

    scheduler.AddTaskToQueue(&task);
    scheduler.AddTaskToQueue(&task2);

    scheduler.WaitForTask(&task);
    scheduler.WaitForTask(&task2);

    scheduler.Cleanup();
}