#pragma once

#include <functional>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

#include "engine/utils/graph.hpp"
#include "engine/utils/type_info.hpp"

namespace engine::core {
    class Engine;
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
        ModuleStage(Stage stage, StageFunction function);

        Stage m_stage;
        std::function<void()> m_function;
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

    class Module : public engine::utils::Node {
        friend ModuleRegistry;

      protected:
        Engine* m_engine;

        void addStage(Stage stage, const std::function<void(void)>& function);

        template <typename T,
                  typename = std::enable_if<std::is_base_of<Module, T>::value>>
        void addSubmodule(T* submodule)
        {
            m_submodules.insert(
                std::pair(utils::TypeInfo<Module>::getTypeId<T>(), submodule));
        }

        template <typename... Args>
        void require(Requires<Args...> require = {})
        {
            m_require = require.get();
        }

      private:
        std::vector<ModuleStage> m_stages;
        std::vector<utils::TypeId> m_require;
        std::unordered_map<utils::TypeId, Module*> m_submodules;
    };

    class ModuleRegistry {
      public:
        template <typename T,
                  typename = std::enable_if<std::is_base_of<Module, T>::value>>
        std::shared_ptr<Module> registerModule(T* module)
        {
            auto ptr = std::shared_ptr<T>(module);
            registerModule(ptr);
            return ptr;
        }

        template <typename T,
                  typename = std::enable_if<std::is_base_of<Module, T>::value>>
        std::shared_ptr<Module> registerModule(std::shared_ptr<T> module)
        {
            registerModule(utils::TypeInfo<Module>::getTypeId<T>(), module);
            return module;
        }

        std::shared_ptr<Module> registerModule(utils::TypeId typeId,
                                               const std::shared_ptr<Module>& module)
        {
            m_modules.insert(std::pair(typeId, module));
            return module;
        }

        void initialize(Engine* engine);

        void callStage(Stage stage);

      private:
        void registerSubmodules(const std::shared_ptr<Module>& module);

        std::unordered_multimap<utils::TypeId, std::shared_ptr<Module>> m_modules;
        std::unordered_map<Stage, std::vector<ModuleStage>> m_stages;
    };
} // namespace engine::core