#pragma once

#include "Engine/Util/TypeInfo.hpp"

namespace Engine {
    template <typename Base>
    class ObjectRegistry {
      public:
        class RegistryValue {
          public:
            std::function<std::shared_ptr<Base>()> Create;
            std::vector<TypeId> Required = {};
        };

        static auto Registry() -> std::unordered_map<TypeId, RegistryValue>&
        {
            static std::unordered_map<TypeId, RegistryValue> impl;
            return impl;
        }

        template <typename... Args>
        class Requires {
          public:
            [[nodiscard]] auto Get() const -> std::vector<TypeId>
            {
                std::vector<TypeId> required;
                (required.emplace_back(TypeInfo<Base>::template GetTypeId<Args>()), ...);
                return required;
            }
        };

        template <typename T>
        class Registrar : public Base {
          public:
            static auto Get() -> std::shared_ptr<T>
            {
                return instance;
            }

          protected:
            inline static std::shared_ptr<T> instance;

            template <typename... Args>
            static auto Register(Requires<Args...>&& required = {}) -> bool
            {
                ObjectRegistry::Registry()[TypeInfo<Base>::template GetTypeId<T>()] = {
                    []() {
                        instance = std::make_shared<T>();
                        return instance;
                    },
                    required.Get()};
                return true;
            }
        };
    };

    class Module : public ObjectRegistry<Module> {
      public:
        enum class Stage { Init, Input, Update, Render, Cleanup };

        using Index = std::pair<unsigned int, TypeId>;

        [[nodiscard]] virtual auto GetName() const -> const char* = 0;

        virtual void Init();
        virtual void Input();
        virtual void Update();
        virtual void Render();
        virtual void Cleanup();
    };

    template class TypeInfo<Module>;

    class ModuleManager {
      public:
        template <typename T>
        void PushModule(T* module);

        template <typename T>
        auto PushModule() -> std::shared_ptr<T>;

        template <typename T>
        auto PopModule() -> std::shared_ptr<T>;

        void CallStage(Module::Stage stage);

        template <typename T>
        void CallModule(Module::Stage stage);

      private:
        uint8_t nextModuleId = 0;

        std::map<Module::Index, std::shared_ptr<Module>> modules;

        template <typename T>
        auto InitializeModule(TypeId typeId) -> std::shared_ptr<T>;
    };

    template <typename T>
    auto ModuleManager::InitializeModule(TypeId typeId) -> std::shared_ptr<T>
    {
        ObjectRegistry<Module>::RegistryValue registryValue =
            ObjectRegistry<Module>::Registry()[typeId];

        for (const TypeId required : registryValue.Required) {
            auto requiredFound = std::find_if(
                modules.begin(), modules.end(),
                [required](const std::pair<Module::Index, std::shared_ptr<Module>>& x) {
                    return x.first.second == required;
                });

            if (requiredFound == modules.end()) {
                InitializeModule<T>(required);
            }
        }

        std::shared_ptr<Module> module = registryValue.Create();
        modules[Module::Index(nextModuleId, typeId)] = module;
        nextModuleId++;

        return std::static_pointer_cast<T>(module);
    }

    template <typename T>
    void ModuleManager::PushModule(T* module)
    {
        auto typeId = TypeInfo<Module>::GetTypeId<T>();

        auto moduleFound = std::find_if(
            modules.begin(), modules.end(),
            [typeId](const std::pair<Module::Index, std::shared_ptr<Module>>& x) {
                return x.first.second == typeId;
            });

        if (moduleFound == modules.end()) {

            ObjectRegistry<Module>::RegistryValue registryValue =
                ObjectRegistry<Module>::Registry()[typeId];

            for (const TypeId required : registryValue.Required) {
                auto requiredFound =
                    std::find_if(modules.begin(), modules.end(),
                                 [required](const std::pair<Module::Index, Module*> x) {
                                     return x.first.second == required;
                                 });

                if (requiredFound == modules.end()) {
                    InitializeModule<T>(required);
                }
            }

            modules[Module::Index(nextModuleId, typeId)] = std::unique_ptr(module);
            nextModuleId++;
        }
        else {
            ENGINE_CORE_ERROR("Try to add module twice type: {}", typeId);
        }
    }

    template <typename T>
    auto ModuleManager::PushModule() -> std::shared_ptr<T>
    {
        TypeId typeId = TypeInfo<Module>::GetTypeId<T>();

        auto moduleFound = std::find_if(
            modules.begin(), modules.end(),
            [typeId](const std::pair<Module::Index, std::shared_ptr<Module>>& x) {
                return x.first.second == typeId;
            });

        if (moduleFound == modules.end()) {
            return InitializeModule<T>(typeId);
        }

        ENGINE_CORE_ERROR("Try to add module twice type: {}", typeId);
        return nullptr;
    }

    template <typename T>
    auto ModuleManager::PopModule() -> std::shared_ptr<T>
    {
        TypeId typeId = TypeInfo<Module>::GetTypeId<T>();

        auto moduleFound = std::find_if(
            modules.begin(), modules.end(),
            [typeId](const std::pair<Module::Index, std::shared_ptr<Module>>& x) {
                return x.first.second == typeId;
            });

        if (moduleFound != modules.end()) {
            T* module = static_cast<T*>(moduleFound->second);
            modules.erase(moduleFound);
            return module;
        }

        ENGINE_CORE_DEV_ERROR("Try to pop unknown module type: {}", typeId);
        return nullptr;
    }

    template <typename T>
    void ModuleManager::CallModule(Module::Stage stage)
    {
        auto typeId = TypeInfo<Module>::GetTypeId<T>();

        auto moduleFound = std::find_if(
            modules.begin(), modules.end(),
            [typeId](const std::pair<Module::Index, std::shared_ptr<Module>>& x) {
                return x.first.second == typeId;
            });

        if (moduleFound != modules.end()) {
            Module* module = moduleFound->second;

            switch (stage) {
                case Module::Stage::Init:
                    ENGINE_CORE_DEBUG("Init module: {}", module->GetName());
                    module->Init();
                    break;
                case Module::Stage::Input:
                    module->Input();
                    break;
                case Module::Stage::Update:
                    module->Update();
                    break;
                case Module::Stage::Render:
                    module->Render();
                    break;
                case Module::Stage::Cleanup:
                    ENGINE_CORE_DEBUG("Cleanup module: {}", module->GetName());
                    module->Cleanup();
                    break;
            }
        }
        else {
            ENGINE_CORE_DEV_ERROR("Call unknow module type: ", typeId);
        }
    }
} // namespace Engine