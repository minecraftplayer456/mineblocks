#include "Engine.hpp"

namespace Engine {
    Engine::Engine(Application* p_App)
    {
        m_App = p_App;
    }

    void Engine::Run()
    {
        init();
        loop();
        cleanup();
    }

    void Engine::init()
    {
        Log::Init();

        ENGINE_CORE_INFO("Running {} v{}", m_App->GetName(),
                         m_App->GetVersion().ToString());

        // m_ModuleManager.PushModule(m_App);

        // m_ModuleManager.CallStage(ModuleStage::Init);
    }

    void Engine::loop()
    {
        ENGINE_CORE_DEBUG("Run game loop");

        m_Running = true;

        while (m_Running) {
            // m_ModuleManager.CallStage(ModuleStage::Input);
            // m_ModuleManager.CallStage(ModuleStage::Update);
            // m_ModuleManager.CallStage(ModuleStage::Render);
        }
    }

    void Engine::cleanup()
    {
        ENGINE_CORE_INFO("Cleaning up");

        // m_ModuleManager.CallStage(ModuleStage::Cleanup);
    }

    /*const ModuleManager& Engine::GetModuleManager() const
    {
        //return m_ModuleManager;
    }*/

    Application* Engine::GetApplication() const
    {
        return m_App;
    }
} // namespace Engine