#include "EntryPoint.hpp"

const char* TestEvent::GetName() const
{
    return "TestEvent";
}

Engine::ModuleStage TestEvent::GetCallStage() const
{
    return Engine::ModuleStage::Init;
}

const char* TestEvent2::GetName() const
{
    return "TestEvent2";
}

Engine::ModuleStage TestEvent2::GetCallStage() const
{
    return Engine::ModuleStage::Cleanup;
}

bool TestEventHandler::Handle(const TestEvent& p_Event)
{
    std::cout << "Event" << std::endl;
    return false;
}

bool TestEventHandler2::Handle(const TestEvent2& p_Event)
{
    std::cout << "Event2" << std::endl;
    return false;
}

int main(int argc, char** argv)
{
    /*auto* app = Engine::CreateApplication();
    auto engine = Engine::Engine(app);

    engine.Run();

    delete app;*/

    TestEvent event;
    TestEvent2 event2;
    TestEventHandler handler;
    TestEventHandler2 handler2;
    Engine::EventBus bus;

    bus.RegisterHandler<TestEvent>(handler);
    bus.RegisterHandler<TestEvent2>(handler2);
    bus.PushEvent<TestEvent>(event);
    bus.PushEvent<TestEvent2>(event2);
    bus.NotifyStage(Engine::ModuleStage::Init);
}