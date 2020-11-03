#include "Module.hpp"

namespace Engine {
    Module::Module(const char* p_Name)
        : m_Name(p_Name)
    {
    }

    const char* Module::GetName() const
    {
        return m_Name;
    }

    ModuleManager::~ModuleManager()
    {
        for (const auto& [_, module] : m_Modules) {
            delete module;
        }
    }

    void ModuleManager::PushModule(Module* module)
    {
        m_Modules[module->m_Name] = module;
        m_Dirty = true;
    }

    void ModuleManager::PopModule(const char* p_Name)
    {
        auto it = m_Modules.find(p_Name);
        if (it != m_Modules.end()) {
            m_Modules.erase(it);
        }
        else {
            ENGINE_CORE_WARN("Module to delete not found: {}", p_Name);
        }
    }

    void ModuleManager::ResortModules()
    {
        ENGINE_CORE_DEBUG("Resort module dependencies");

        std::vector<Node*> nodes;

        for (const auto& [_, module] : m_Modules) {
            module->m_InNeighbours.clear();
            module->m_OutNeighbours.clear();
        }

        for (const auto& [name, module] : m_Modules) {
            for (const auto& dependency : module->m_Dependencies) {
                auto it = m_Modules.find(dependency);
                if (it != m_Modules.end()) {
                    it->second->m_OutNeighbours.push_back(module);
                    module->m_InNeighbours.push_back(it->second);
                }
                else {
                    ENGINE_CORE_WARN("Failed to find module dependency: {}", dependency);
                }
            }

            nodes.push_back(module);
        }

        Graph graph(nodes);
        graph.SortDependencies();

        /*m_Modules.clear();

        for (const auto& node : graph.GetSortedNodes()) {
            auto module = reinterpret_cast<Module*>(node);
            m_Modules[module->m_Name] = module;
        }*/

        for (const auto& node : graph.GetSortedNodes()) {
            auto module = static_cast<Module*>(node);

            if (module->m_InitFunction != nullptr) {
                auto& vec = m_Functions[ModuleStage::Init];
                vec.push_back(module->m_InitFunction);
            }

            if (module->m_InputFunction != nullptr) {
                auto& vec = m_Functions[ModuleStage::Input];
                vec.push_back(module->m_InputFunction);
            }

            if (module->m_UpdateFunction != nullptr) {
                auto& vec = m_Functions[ModuleStage::Update];
                vec.push_back(module->m_UpdateFunction);
            }

            if (module->m_RenderFunction != nullptr) {
                auto& vec = m_Functions[ModuleStage::Render];
                vec.push_back(module->m_RenderFunction);
            }

            if (module->m_CleanupFunction != nullptr) {
                auto& vec = m_Functions[ModuleStage::Cleanup];
                vec.push_back(module->m_CleanupFunction);
            }
        }

        m_Dirty = false;
    }

    void ModuleManager::CallStage(ModuleStage stage)
    {
        if (m_Dirty) {
            ResortModules();
        }

        for (const auto& function : m_Functions[stage]) {
            function();
        }

        /*for (const auto& [name, module] : m_Modules) {
            switch (stage) {
                case ModuleStage::Init:
                    if (module->m_InitFunction) {
                        ENGINE_CORE_INFO("Initialize module: {}", name);
                        module->m_InitFunction();
                    }
                    break;
                case ModuleStage::Input:
                    if (module->m_InputFunction) {
                        module->m_InputFunction();
                    }
                    break;
                case ModuleStage::Update:
                    if (module->m_UpdateFunction) {
                        module->m_UpdateFunction();
                    }
                    break;
                case ModuleStage::Render:
                    if (module->m_RenderFunction) {
                        module->m_RenderFunction();
                    }
                    break;
                case ModuleStage::Cleanup:
                    if (module->m_CleanupFunction) {
                        ENGINE_CORE_INFO("Cleanup module: {}", name);
                        module->m_CleanupFunction();
                    }
                    break;
            }
        }*/
    }
} // namespace Engine