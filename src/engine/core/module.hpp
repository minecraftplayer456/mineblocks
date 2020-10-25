#pragma once

#include <functional>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

#include "engine/utils/graph.hpp"
#include "engine/utils/type_info.hpp"

namespace engine::core {
    class ModuleManager;

    enum class ModuleLifecycle {
        Init,

        Input,
        Update,
        Render,

        Cleanup
    };

    class ModuleStage {
      public:
        ModuleLifecycle m_stage{};
        std::function<void()> m_function;
    };

    class Module : public utils::Node {
        friend ModuleManager;

      protected:
        template <typename T,
                  typename = std::enable_if<std::is_base_of<Module, T>::value>>
        std::shared_ptr<T> addSubmodule()
        {
            auto typeId = utils::TypeInfo<Module>::getTypeId<T>();
            auto module = std::make_shared<T>();
            m_submodules[typeId] = module;
            return module;
        }

        template <typename T,
            typename = std::enable_if<std::is_base_of<Module, T>::value>>
        std::shared_ptr<T> addSubmodule(T* module){
            auto typeId = utils::TypeInfo<Module>::getTypeId<T>();
            auto modulePtr = std::shared_ptr<T>(module);
            m_submodules[typeId] = modulePtr;
            return modulePtr;
        }

        template <typename T,
                  typename = std::enable_if<std::is_base_of<Module, T>::value>>
        void require()
        {
            m_require.push_back(utils::TypeInfo<Module>::getTypeId<T>());
        }

        template <typename T,
                  typename = std::enable_if<std::is_base_of<Module, T>::value>>
        std::shared_ptr<T> getModule();

        void addStage(ModuleLifecycle stage, std::function<void()> function)
        {
            ModuleStage moduleStage;
            moduleStage.m_stage = stage;
            moduleStage.m_function = std::move(function);
            m_stages.push_back(moduleStage);
        }

      private:
        ModuleManager* m_moduleManager;

        std::vector<ModuleStage> m_stages;
        std::vector<utils::TypeId> m_require;
        std::unordered_map<utils::TypeId, std::shared_ptr<Module>> m_submodules;
    };

    class ModuleManager {
      public:
        template <typename T,
                  typename = std::enable_if<std::is_base_of<Module, T>::value>>
        void registerModule(T* module)
        {
            auto typeId = utils::TypeInfo<Module>::getTypeId<T>();
            auto modulePtr = std::shared_ptr<Module>(module);
            addModules(modulePtr->m_submodules);
            m_modules[typeId] = modulePtr;
        }

        void addModules(
            const std::unordered_map<utils::TypeId, std::shared_ptr<Module>>& modules)
        {
            for (const auto& [moduleType, module] : modules) {
                addModules(module->m_submodules);
                m_modules[moduleType] = module;
            }
        }

        template <typename T,
                  typename = std::enable_if<std::is_base_of<Module, T>::value>>
        std::shared_ptr<T> getModule()
        {
            auto typeId = utils::TypeInfo<Module>::getTypeId<T>();
            return std::reinterpret_pointer_cast<T>(m_modules[typeId]);
        }

        void init();

        void callStage(ModuleLifecycle stage);

      private:
        std::unordered_map<utils::TypeId, std::shared_ptr<Module>> m_modules;
        std::unordered_multimap<ModuleLifecycle, ModuleStage> m_stages;
    };

    template <typename T, typename>
    std::shared_ptr<T> Module::getModule()
    {
        return m_moduleManager->getModule<T>();
    }
} // namespace engine::core