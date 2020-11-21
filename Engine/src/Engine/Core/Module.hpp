#pragma once

#include "Engine/Util/TypeInfo.hpp"

namespace Engine {
    template <typename Base>
    class ObjectRegistry {
      public:
        class RegistryValue {
          public:
            std::function<Base*()> create;
            std::vector<TypeId> required;
        };

        static std::unordered_map<TypeId, RegistryValue>& Registry()
        {
            static std::unordered_map<TypeId, RegistryValue> impl;
            return impl;
        }

        template <typename... Args>
        class Requires {
          public:
            [[nodiscard]] std::vector<TypeId> Get() const
            {
                std::vector<TypeId> required;
                (required.emplace_back(TypeInfo<Base>::template GetTypeId<Args>()), ...);
                return required;
            }
        };

        template <typename T>
        class Registrar : public Base {
          public:
            static T* Get()
            {
                return Instance;
            }

          protected:
            inline static T* Instance = nullptr;

            template <typename... Args>
            static bool Register(const char* name, Requires<Args...>&& required = {})
            {
                ObjectRegistry::Registry()[TypeInfo<Base>::template GetTypeId<T>()] = {
                    []() {
                        Instance = new T();
                        return Instance;
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

        virtual void Init();
        virtual void Input();
        virtual void Update();
        virtual void Render();
        virtual void Cleanup();
    };

    template class TypeInfo<Module>;

    class ModuleManager {
      public:
        ~ModuleManager();

        template <typename T>
        void PushModule(T* module);

        template <typename T>
        T* PushModule();

        template <typename T>
        T* PopModule();

        void CallStage(Module::Stage stage);

      private:
        uint8_t NextModuleId = 0;

        std::map<Module::Index, Module*> Modules;

        template <typename T>
        T* InitializeModule(TypeId typeId);
    };

    template <typename T>
    T* ModuleManager::InitializeModule(TypeId typeId)
    {
        ObjectRegistry<Module>::RegistryValue registryValue =
            ObjectRegistry<Module>::Registry()[typeId];

        for (const TypeId required : registryValue.required) {
            auto requiredFound =
                std::find_if(Modules.begin(), Modules.end(),
                             [required](const std::pair<Module::Index, Module*> x) {
                                 return x.first.second == required;
                             });

            if (requiredFound == Modules.end()) {
                InitializeModule<T>(required);
            }
        }

        T* module = static_cast<T*>(registryValue.create());
        Modules[Module::Index(NextModuleId, typeId)] = module;
        NextModuleId++;

        return module;
    }

    template <typename T>
    void ModuleManager::PushModule(T* module)
    {
        auto typeId = TypeInfo<Module>::GetTypeId<T>();

        auto moduleFound =
            std::find_if(Modules.begin(), Modules.end(),
                         [typeId](const std::pair<Module::Index, Module*> x) {
                             return x.first.second == typeId;
                         });

        if (moduleFound == Modules.end()) {

            ObjectRegistry<Module>::RegistryValue registryValue =
                ObjectRegistry<Module>::Registry()[typeId];

            for (const TypeId required : registryValue.required) {
                auto requiredFound =
                    std::find_if(Modules.begin(), Modules.end(),
                                 [required](const std::pair<Module::Index, Module*> x) {
                                     return x.first.second == required;
                                 });

                if (requiredFound == Modules.end()) {
                    InitializeModule<T>(required);
                }
            }

            Modules[Module::Index(NextModuleId, typeId)] = module;
            NextModuleId++;
        }
        else {
            ENGINE_CORE_ERROR("Try to add module twice type: {}", typeId);
        }
    }

    template <typename T>
    T* ModuleManager::PushModule()
    {
        TypeId typeId = TypeInfo<Module>::GetTypeId<T>();

        auto moduleFound =
            std::find_if(Modules.begin(), Modules.end(),
                         [typeId](const std::pair<Module::Index, Module*> x) {
                             return x.first.second == typeId;
                         });

        if (moduleFound == Modules.end()) {
            return InitializeModule<T>(typeId);
        }
        else {
            ENGINE_CORE_ERROR("Try to add module twice type: {}", typeId);
            return nullptr;
        }
    }

    template <typename T>
    T* ModuleManager::PopModule()
    {
        TypeId typeId = TypeInfo<Module>::GetTypeId<T>();

        auto moduleFound =
            std::find_if(Modules.begin(), Modules.end(),
                         [typeId](const std::pair<Module::Index, Module*> x) {
                             return x.first.second == typeId;
                         });

        if (moduleFound != Modules.end()) {
            T* module = static_cast<T*>(moduleFound->second);
            Modules.erase(moduleFound);
            return module;
        }
        else {
            ENGINE_CORE_DEV_ERROR("Try to pop unknown module type: {}", typeId);
            return nullptr;
        }
    }
} // namespace Engine