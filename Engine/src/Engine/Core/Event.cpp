#include "Event.hpp"

namespace Engine {
    void EventBus::NotifyAll()
    {
        for ([[maybe_unused]] auto& [_, index] : events) {
            CallEvent(index);
        }

        events.clear();
    }

    void EventBus::NotifyStage(Event::Stage stage)
    {
        for (auto it = events.begin(); it != events.end(); it++) {
            if ((it->first & stage) != 0) {
                CallEvent(it->second);
                events.erase(it);
            }
        }
    }

    void EventBus::CallEvent(EventIndex& index)
    {
        TypeId eventTypeId = index.first;
        std::unique_ptr<Event>& event = index.second;

        auto handlerFound = handlers.equal_range(eventTypeId);

        if (handlerFound.first != handlerFound.second) {
            ENGINE_CORE_DEBUG("Call event: {}", event->GetName());

            for (auto it = handlerFound.first; it != handlerFound.second; it++) {
                std::shared_ptr<EventHandler<Event>> handler = it->second;
                if (handler->Handle(*event)) {
                    break;
                }
            }
        }
    }
} // namespace Engine