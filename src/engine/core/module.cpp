#include "module.hpp"

namespace engine::core {
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
        for (const auto& stage : module->m_stages) {
            auto modules = &m_modules[stage];
            modules->push_back(std::shared_ptr<Module>(module));
        }
    }

    void ModuleRegistry::callStage(Stage stage)
    {
        for (auto& module : m_modules[stage]) {
            switch (stage) {
                case Stage::init:
                    module->init();
                case Stage::input:
                    module->input();
                case Stage::update:
                    module->update();
                case Stage::render:
                    module->render();
                case Stage::cleanup:
                    module->cleanup();
            }
        }
    }
} // namespace engine::core