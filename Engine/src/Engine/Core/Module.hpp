#pragma once

#include <Engine/Util/Graph.hpp>

namespace Engine {
    class ModuleManager;

    using ModuleFunction = std::function<void()>;

    enum class ModuleStage { Init, Input, Update, Render, Cleanup };

    class Module : private Node {
        friend ModuleManager;

      public:
        explicit Module(const char* p_Name);

        [[nodiscard]] virtual const char* GetName() const;

      protected:
        const char* m_Name;

        std::vector<const char*> m_Dependencies;

        ModuleFunction m_InitFunction = nullptr;
        ModuleFunction m_InputFunction = nullptr;
        ModuleFunction m_UpdateFunction = nullptr;
        ModuleFunction m_RenderFunction = nullptr;
        ModuleFunction m_CleanupFunction = nullptr;
    };

    class ModuleManager {
      public:
        ~ModuleManager();

        void PushModule(Module* module);
        void PopModule(const char* name);

        void ResortModules();

        void CallStage(ModuleStage stage);

      private:
        bool m_Dirty = false;

        std::unordered_map<const char*, Module*> m_Modules;
        std::unordered_map<ModuleStage, std::vector<ModuleFunction>> m_Functions;
    };
} // namespace Engine