#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

namespace engine::core {
    class ModuleRegistry;
    class Module;

    enum class Stage {
        init,

        input,
        update,
        render,

        cleanup
    };

    class Module {
        friend ModuleRegistry;

      protected:
        virtual void init();
        virtual void input();
        virtual void update();
        virtual void render();
        virtual void cleanup();

        std::vector<Stage> m_stages;
    };

    class ModuleRegistry {
        friend Module;

      public:
        void registerModule(Module* module);

        void callStage(Stage stage);

      private:
        std::vector<std::shared_ptr<Module>> m_modules;
    };
} // namespace engine::core