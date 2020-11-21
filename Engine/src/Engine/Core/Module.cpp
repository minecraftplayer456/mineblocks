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

    ModuleManager::~ModuleManager()
    {
        for (const auto [_, module] : Modules) {
            delete module;
        }
    }

    void ModuleManager::CallStage(Module::Stage stage)
    {
        switch (stage) {
            case Module::Stage::Init:
                for (const auto [_, module] : Modules) {
                    module->Init();
                }
                break;
            case Module::Stage::Input:
                for (const auto [_, module] : Modules) {
                    module->Input();
                }
                break;
            case Module::Stage::Update:
                for (const auto [_, module] : Modules) {
                    module->Update();
                }
                break;
            case Module::Stage::Render:
                for (const auto [_, module] : Modules) {
                    module->Render();
                }
                break;
            case Module::Stage::Cleanup:
                for (const auto [_, module] : Modules) {
                    module->Cleanup();
                }
                break;
        }
    }
} // namespace Engine