#include "Event.hpp"

namespace Engine {
    void EventBus::NotifyAll()
    {
        for (const auto& [_, event] : m_Events) {
            for (auto it = m_Handlers.find(event->GetTypeId()); it != m_Handlers.end();
                 it++) {
                if (it->second->Handle(*event)) {
                    break;
                }
            }
        }
    }

    void EventBus::NotifyStage(ModuleStage p_Stage)
    {
        for (auto it = m_Events.find(p_Stage); it != m_Events.end(); it++) {
            auto event = it->second;

            for (auto it2 = m_Handlers.find(event->GetTypeId()); it2 != m_Handlers.end();
                 it2++) {
                if (it2->second->Handle(*event)) {
                    break;
                }
            }
        }
    }
} // namespace Engine