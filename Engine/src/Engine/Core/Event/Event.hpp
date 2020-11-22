#pragma once

#include "Engine/Core/Module.hpp"
#include "Engine/Util/TypeInfo.hpp"

namespace Engine {
    class Event {
      public:
        enum Stage {
            Never = 0,
            Init = BIT(0),
            Input = BIT(1),
            Update = BIT(2),
            Render = BIT(3),
            Cleanup = BIT(4),
            Always = Init | Input | Update | Render | Cleanup
        };

        virtual const char* GetName() const = 0;
        virtual int GetCalledAt() const = 0;
    };

    template <typename T>
    class EventHandler {
      public:
        virtual bool Handle(const T& event) = 0;
    };

    template <typename T>
    class FuncHandler : public EventHandler<T> {
      public:
        explicit FuncHandler(const std::function<bool(const T&)>& func)
            : Func(func)
        {
        }

        bool Handle(const T& event) override
        {
            return Func(event);
        };

      private:
        const std::function<bool(const T&)> Func;
    };

    class EventBus {
      public:
        using EventIndex = std::pair<TypeId, std::unique_ptr<Event>>;

        template <typename T>
        void RegisterHandler(std::shared_ptr<EventHandler<T>> handler);
        template <typename T>
        void UnrigesterHandler(std::shared_ptr<EventHandler<T>> handler);

        template <typename T>
        std::shared_ptr<EventHandler<T>>
        RegisterHandler(std::function<bool(const T&)> func);

        template <typename T>
        void PushEvent(T* event);

        void NotifyAll();
        void NotifyStage(Event::Stage stage);

      private:
        std::multimap<Event::Stage, EventIndex> Events;
        std::multimap<TypeId, std::shared_ptr<EventHandler<Event>>> Handlers;

        void CallEvent(EventIndex& index);
    };

    template <typename T>
    void EventBus::RegisterHandler(std::shared_ptr<EventHandler<T>> handler)
    {
        auto eventTypeId = TypeInfo<Event>::GetTypeId<T>();

        Handlers.insert(std::pair(
            eventTypeId, std::reinterpret_pointer_cast<EventHandler<Event>>(handler)));
    }

    template <typename T>
    void EventBus::UnrigesterHandler(std::shared_ptr<EventHandler<T>> handler)
    {
        auto eventTypeId = TypeInfo<Event>::GetTypeId<T>();

        auto handlerFound = std::find_if(
            Handlers.begin(), Handlers.end(),
            [eventTypeId,
             handler](const std::pair<TypeId, std::shared_ptr<EventHandler<Event>>>& x) {
                return x.second ==
                           std::reinterpret_pointer_cast<EventHandler<Event>>(handler) &&
                       x.first == eventTypeId;
            });

        if (handlerFound != Handlers.end()) {
            Handlers.erase(handlerFound);
        }
        else {
            ENGINE_CORE_DEV_ERROR(
                "Try to remove unknown event handler with event type: {}", eventTypeId);
        }
    }

    template <typename T>
    std::shared_ptr<EventHandler<T>>
    EventBus::RegisterHandler(std::function<bool(const T&)> func)
    {
        std::shared_ptr<EventHandler<T>> handler = std::make_shared<FuncHandler<T>>(func);
        RegisterHandler<T>(handler);
        return handler;
    }

    template <typename T>
    void EventBus::PushEvent(T* event)
    {
        auto typeId = TypeInfo<Event>::GetTypeId<T>();

        Events.insert(std::pair(static_cast<Event::Stage>(event->GetCalledAt()),
                                EventIndex(typeId, std::unique_ptr<T>(event))));
    }
} // namespace Engine