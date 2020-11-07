#include "EntryPoint.hpp"

class TestLifecycle : public Engine::Lifecycle<TestLifecycle> {
  public:
    TestLifecycle()
    {
        m_Info.Name = "TestModule";
        m_Info.Static = true;
        m_Info.Functions[Engine::LifecycleState::Init] = [this]() { Init(); };
    }

    void Init()
    {
        ENGINE_INFO("Init");
    }
};

class TestLifecycle2 : public Engine::Lifecycle<TestLifecycle2> {
  public:
    TestLifecycle2(TestLifecycle* lifecycleTest)
    {
        m_Info.Name = "TestModule2";
        m_Info.Static = true;
        m_Info.Functions[Engine::LifecycleState::Init] = [this]() { Init(); };
        m_Info.Dependencies.push_back(
            reinterpret_cast<Lifecycle<LifecycleObject>* const>(lifecycleTest));
    }

    void Init()
    {
        ENGINE_INFO("Init2");
    }
};

int main(int argc, char** argv)
{
    /*auto* app = Engine::CreateApplication();
    auto engine = Engine::Engine(app);

    engine.Run();

    delete app;*/

    Engine::Log::Init();

    auto* lifecycle = new TestLifecycle;
    // auto* lifecycle2 = new TestLifecycle2(lifecycle);
    Engine::LifecycleManager manager;

    // auto testLifecycle = manager.Push<TestLifecycle>();
    // manager.Push<TestLifecycle2>(testLifecycle);

    manager.Push(
        reinterpret_cast<Engine::Lifecycle<Engine::LifecycleObject>*>(lifecycle));
    manager.Push(
        reinterpret_cast<Engine::Lifecycle<Engine::LifecycleObject>*>(lifecycle));

    manager.CallState(Engine::LifecycleState::Init);
}