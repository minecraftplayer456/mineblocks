#include "Module.hpp"

namespace Engine {
    void Module::Init()
    {
    }

    void Module::Input()
    {
    }

    void Module::Update()
    {
    }

    void Module::Render()
    {
    }

    void Module::Cleanup()
    {
    }

    void ModuleManager::CallStage(Module::Stage stage)
    {
        switch (stage) {
            case Module::Stage::Init:
                for ([[maybe_unused]] const auto& [_, module] : modules) {
                    ENGINE_CORE_DEBUG("Init module: {}", module->GetName());
                    module->Init();
                }
                break;
            case Module::Stage::Input:
                for (const auto& [_, module] : modules) {
                    module->Input();
                }
                break;
            case Module::Stage::Update:
                for (const auto& [_, module] : modules) {
                    module->Update();
                }
                break;
            case Module::Stage::Render:
                for (const auto& [_, module] : modules) {
                    module->Render();
                }
                break;
            case Module::Stage::Cleanup:
                for (const auto& [_, module] : modules) {
                    ENGINE_CORE_DEBUG("Cleanup module: {}", module->GetName());
                    module->Cleanup();
                }
                break;
        }
    }
} // namespace Engine