#include "Engine/Common/Scheduler.hpp"

class TestTask : public enki::ITaskSet {
  public:
    void ExecuteRange(enki::TaskSetPartition range_, uint32_t threadnum_) override
    {
        ENGINE_CORE_INFO("Task: {}, {}, {}", threadnum_, range_.start, range_.end);
    }
};

class TestTask2 : public enki::ITaskSet {
  public:
    void ExecuteRange(enki::TaskSetPartition range_, uint32_t threadnum_) override
    {
        ENGINE_CORE_INFO("Task2: {}, {}, {}", threadnum_, range_.start, range_.end);
    }
};

int main()
{
    Engine::Log::Initialize();

    enki::TaskScheduler scheduler;
    scheduler.Initialize(1);

    TestTask task;
    TestTask2 task2;
    // task2.m_Priority = enki::TASK_PRIORITY_HIGH;
    // TestTask task3;
    // TestTask task4;

    scheduler.AddTaskSetToPipe(&task);
    scheduler.AddTaskSetToPipe(&task2);
    // scheduler.AddTaskSetToPipe(&task3);
    // scheduler.AddTaskSetToPipe(&task4);

    scheduler.WaitforTask(&task);
    scheduler.WaitforTask(&task2);
    // scheduler.WaitforTask(&task3);
    // scheduler.WaitforTask(&task4);

    scheduler.WaitforAllAndShutdown();
}