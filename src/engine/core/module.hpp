#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "engine/utils/type_info.hpp"

namespace engine::core {
    class ModuleRegistry;
    class Module;

    enum class Stage {
        Init,

        Input,
        Update,
        Render,

        Cleanup
    };

    using StageFunction = std::function<void()>;

    class ModuleStage {
        friend ModuleRegistry;

      public:
        ModuleStage(Stage stage, StageFunction function,
                    std::vector<utils::TypeId> require);

        Stage m_stage;
        std::function<void()> m_function;
        std::vector<utils::TypeId> m_require;
    };

    template <typename... Args>
    class Requires {
      public:
        [[nodiscard]] std::vector<engine::utils::TypeId> get() const
        {
            std::vector<engine::utils::TypeId> require;
            (require.emplace_back(
                 engine::utils::TypeInfo<Module>::template getTypeId<Args>()),
             ...);
            return require;
        }
    };

    class Module {
        friend ModuleRegistry;

      protected:
        template <typename... Args>
        void addStage(Stage stage, const std::function<void(void)>& function,
                      Requires<Args...> require = {})
        {
            m_stages.emplace_back(stage, function, require.get());
        }

      private:
        std::vector<ModuleStage> m_stages;
    };

    class ModuleRegistry {
      public:
        void registerModule(Module* module);

        void sortStages();

        void callStage(Stage stage);

      private:
        std::vector<std::shared_ptr<Module>> m_modules;
        std::unordered_map<Stage, std::vector<ModuleStage>> m_stages;
    };
} // namespace engine::core