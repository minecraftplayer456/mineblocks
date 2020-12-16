#pragma once

#include <atomic>
#include <mutex>
#include <thread>

#include <enkiTS/TaskScheduler.h>

namespace Engine {
    class Scheduler {
      public:
        Scheduler();
        ~Scheduler();

      private:
        enki::TaskScheduler scheduler;
    };
};