#pragma once

#include "Engine/Core/Module.hpp"

namespace Engine {
    class Event {
      public:
        enum Stage {
            Never = 0,
            Init = Bit(0),
            Input = Bit(1),
            Update = Bit(2),
            Render = Bit(3),
            Cleanup = Bit(4),
            Always = Init | Input | Update | Render | Cleanup
        };

        [[nodiscard]] virtual auto GetName() const -> const char* = 0;
        [[nodiscard]] virtual auto GetCalledAt() const -> int = 0;
    };

    template <typename T>
    class EventHandler {
      public:
        virtual auto Handle(const T& event) -> bool = 0;
    };

    template <typename T>
    class FuncHandler : public EventHandler<T> {
      public:
        explicit FuncHandler(const std::function<bool(const T&)>& func)
            : Func(func)
        {
        }

        auto Handle(const T& event) -> bool override
        {
            return Func(event);
        };

      private:
        const std::function<bool(const T&)> Func;
    };

    class EventBus : public Singleton<EventBus> {
      public:
        inline static const bool Registered = Create();

        using EventIndex = std::pair<TypeId, std::unique_ptr<Event>>;

        template <typename T>
        void RegisterHandler(std::shared_ptr<EventHandler<T>> handler);
        template <typename T>
        void UnrigesterHandler(std::shared_ptr<EventHandler<T>> handler);

        template <typename T>
        auto RegisterHandler(std::function<bool(const T&)> func)
            -> std::shared_ptr<EventHandler<T>>;

        template <typename T>
        void PushEvent(T* event);

        void NotifyAll();
        void NotifyStage(Event::Stage stage);

      private:
        std::multimap<Event::Stage, EventIndex> events = {};
        std::multimap<TypeId, std::shared_ptr<EventHandler<Event>>> handlers = {};

        void CallEvent(EventIndex& index);
    };

    template <typename T>
    void EventBus::RegisterHandler(std::shared_ptr<EventHandler<T>> handler)
    {
        auto eventTypeId = TypeInfo<Event>::GetTypeId<T>();

        handlers.insert(std::pair(
            eventTypeId, std::reinterpret_pointer_cast<EventHandler<Event>>(handler)));
    }

    template <typename T>
    void EventBus::UnrigesterHandler(std::shared_ptr<EventHandler<T>> handler)
    {
        auto eventTypeId = TypeInfo<Event>::GetTypeId<T>();

        auto handlerFound = std::find_if(
            handlers.begin(), handlers.end(),
            [eventTypeId,
             handler](const std::pair<TypeId, std::shared_ptr<EventHandler<Event>>>& x) {
                return x.second ==
                           std::reinterpret_pointer_cast<EventHandler<Event>>(handler) &&
                       x.first == eventTypeId;
            });

        if (handlerFound != handlers.end()) {
            handlers.erase(handlerFound);
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

        events.insert(std::pair(static_cast<Event::Stage>(event->GetCalledAt()),
                                EventIndex(typeId, std::unique_ptr<T>(event))));
    }
} // namespace Engine