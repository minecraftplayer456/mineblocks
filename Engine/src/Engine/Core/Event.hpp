#pragma once

#include "Engine/Core/Module.hpp"
#include "Engine/Util/TypeInfo.hpp"

namespace Engine {
    class EventObject {
      public:
        [[nodiscard]] virtual const char* GetName() const = 0;
        [[nodiscard]] virtual ModuleStage GetCallStage() const = 0;
    };

    template <typename T>
    class Event : public TypeObject<T>, public EventObject {
      public:
        [[nodiscard]] const char* GetName() const override = 0;
        [[nodiscard]] ModuleStage GetCallStage() const override = 0;
    };

    template <typename T>
    class EventHandler {
      public:
        virtual bool Handle(const T& p_Event) = 0;
    };

    class EventBus {
      public:
        template <typename T>
        void RegisterHandler(EventHandler<T>& e);

        template <typename T>
        void PushEvent(T& e);

        void NotifyAll();
        void NotifyStage(ModuleStage p_Stage);

      private:
        std::unordered_multimap<ModuleStage, Event<EventObject>*> m_Events;
        std::unordered_multimap<TypeId, EventHandler<Event<EventObject>>*> m_Handlers;
    };

    template <typename T>
    void EventBus::RegisterHandler(EventHandler<T>& e)
    {
        m_Handlers.insert(std::make_pair<TypeId, EventHandler<Event<EventObject>>*>(
            TypeInfo<EventObject>::GetTypeId<T>(),
            reinterpret_cast<EventHandler<Event<EventObject>>*>(&e)));
    }

    template <typename T>
    void EventBus::PushEvent(T& e)
    {
        auto* event = reinterpret_cast<Event<EventObject>*>(&e);
        m_Events.insert(
            std::pair<ModuleStage, Event<EventObject>*>(event->GetCallStage(), event));
    }
} // namespace Engine