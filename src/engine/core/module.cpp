#include "module.hpp"

namespace engine::core {
    ModuleStage::ModuleStage(Stage stage, StageFunction function)
        : m_stage(stage)
        , m_function(std::move(function))
    {
    }

    void Module::addStage(Stage stage, const std::function<void(void)>& function)
    {
        m_stages.emplace_back(stage, function);
    }

    void ModuleRegistry::registerSubmodules(const std::shared_ptr<Module>& module)
    {
        for (const auto& submodule : module->m_submodules) {
            auto submodulePtr = registerModule(submodule.first,
                                               std::shared_ptr<Module>(submodule.second));
            registerSubmodules(submodulePtr);
        }
    }

    void ModuleRegistry::sortRequirements()
    {
        for (const auto& [_, module] : m_modules) {
            registerSubmodules(module);
        }

        for (const auto& [_, module] : m_modules) {
            for (const auto& requireType : module->m_require) {

                const auto foundRequireTypes = m_modules.equal_range(requireType);
                for (auto it = foundRequireTypes.first; it != foundRequireTypes.second;
                     it++) {
                    it->second->m_inNeighbours.push_back(
                        std::static_pointer_cast<utils::Node>(it->second));

                    module->m_outNeighbours.push_back(
                        std::static_pointer_cast<utils::Node>(it->second));
                }
            }
        }

        utils::Graph graph;

        for (const auto& [_, module] : m_modules) {
            graph.addNode(std::static_pointer_cast<utils::Node>(module));
        }

        graph.sort();

        std::vector<std::shared_ptr<utils::Node>> sortedNodes = graph.getNodes();
        std::vector<std::shared_ptr<Module>> sortedModules;

        sortedModules.reserve(sortedNodes.size());
        for (const auto& node : sortedNodes) {
            sortedModules.push_back(std::reinterpret_pointer_cast<Module>(node));
        }
        std::reverse(sortedModules.begin(), sortedModules.end());

        for (const auto& module : sortedModules) {
            for (const auto& moduleStage : module->m_stages) {
                auto& stages = m_stages[moduleStage.m_stage];
                stages.push_back(moduleStage);
            }
        }
    }

    void ModuleRegistry::callStage(Stage stage)
    {
        for (const auto& moduleStages : m_stages[stage]) {
            moduleStages.m_function();
        }
    }
} // namespace engine::core