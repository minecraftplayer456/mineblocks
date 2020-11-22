#include "Event.hpp"

namespace Engine {
    void EventBus::NotifyAll()
    {
        for (auto& [_, index] : Events) {
            CallEvent(index);
        }

        Events.clear();
    }

    void EventBus::NotifyStage(Event::Stage stage)
    {
        for (auto it = Events.begin(); it != Events.end(); it++) {
            if (it->first & stage) {
                CallEvent(it->second);
                Events.erase(it);
            }
        }
    }

    void EventBus::CallEvent(EventIndex& index)
    {
        TypeId eventTypeId = index.first;
        std::unique_ptr<Event>& event = index.second;

        auto handlerFound = Handlers.equal_range(eventTypeId);

        if (handlerFound.first != handlerFound.second) {
            ENGINE_CORE_DEBUG("Call event: {}", event->GetName());

            for (auto it = handlerFound.first; it != handlerFound.second; it++) {
                std::shared_ptr<EventHandler<Event>> handler = it->second;
                if (handler->Handle(*event))
                    break;
            }
        }
    }
} // namespace Engine