#include "module.hpp"

#include <spdlog/spdlog.h>

#include <utility>

namespace engine::core {
    ModuleStage::ModuleStage(Stage stage, StageFunction function,
                             std::vector<utils::TypeId> require)
        : m_stage(stage)
        , m_function(std::move(function))
        , m_require(std::move(require))
    {
    }

    void ModuleRegistry::registerModule(Module* module)
    {
        m_modules.push_back(std::shared_ptr<Module>(module));
    }

    void ModuleRegistry::sortStages()
    {
        // std::unordered_map<int, ModuleStage> stages;

        for (const auto& module : m_modules) {
            for (const auto& moduleStage : module->m_stages) {

                if (!m_stages.contains(moduleStage.m_stage)) {
                    m_stages[moduleStage.m_stage].push_back(moduleStage);
                }

                for (const auto& sortedStage : m_stages) {

                    for (int i = 0; i < sortedStage.second.size(); i++) {
                        const auto& sortedModuleStage = sortedStage.second[i];

                        for (auto requiresTypeId : moduleStage.m_require) {
                            if (utils::TypeInfo<Module>::getTypeId<typeof(
                                    sortedModuleStage)>() == requiresTypeId) {
                                m_stages[moduleStage.m_stage].emplace(
                                    m_stages[moduleStage.m_stage].begin() + i - 1,
                                    moduleStage);
                            }
                            else {
                                m_stages[moduleStage.m_stage].push_back(moduleStage);
                            }
                        }
                    }
                }
            }
        }

        /*for(const auto& module : m_modules){
            for(auto& stageInModule : module->m_stages){

                for(const auto& sortedStages : m_stages){
                    for(auto sortedModules : sortedStages.second){

                    }
                }
            }
        }*/

        /*for (const auto& module : m_modules) {
            for (const auto& stage : module->m_stages) {
                auto& stages = m_stages[stage.m_stage];
                stages.push_back(stage);
            }
        }*/
    }

    void ModuleRegistry::callStage(Stage stage)
    {
        /*auto result = m_stages.equal_range(stage);

        for(auto it = result.first; it != result.second; it++){
            it->second.m_function();
        }*/

        for (const auto& moduleStages : m_stages[stage]) {
            moduleStages.m_function();
        }
    }
} // namespace engine::core