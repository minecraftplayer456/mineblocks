#include "module.hpp"

namespace engine::core {
    Module::Module()
    {
        m_stages = setupStages();
    }

    std::vector<Stage> Module::setupStages()
    {
    }

    void Module::init()
    {
    }

    void Module::input()
    {
    }

    void Module::update()
    {
    }

    void Module::render()
    {
    }

    void Module::cleanup()
    {
    }

    void ModuleRegistry::registerModule(Module* module)
    {
        m_modules.push_back(std::shared_ptr<Module>(module));
    }

    void ModuleRegistry::callStage(Stage stage)
    {
        for (const auto& module : m_modules) {
            for (auto moduleStages : module->m_stages) {
                if (moduleStages == stage) {
                    switch (moduleStages) {
                        case Stage::init:
                            module->init();
                            break;
                        case Stage::input:
                            module->input();
                            break;
                        case Stage::update:
                            module->update();
                            break;
                        case Stage::render:
                            module->render();
                            break;
                        case Stage::cleanup:
                            module->cleanup();
                            break;
                    }
                }
            }
        }
    }
} // namespace engine::core