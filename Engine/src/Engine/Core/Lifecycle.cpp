#include "Lifecycle.hpp"

namespace Engine {
    LifecycleManager::~LifecycleManager()
    {
        for (const auto* lifecycle : m_Lifecycles) {
            delete lifecycle;
        }
    }

    void LifecycleManager::Push(Lifecycle<LifecycleObject>* p_Lifecycle)
    {
        if (p_Lifecycle->m_Info.Static) {
            if (auto it = m_Statics.find(p_Lifecycle->GetTypeId());
                it != m_Statics.end()) {
                ENGINE_CORE_DEV_ERROR("Try to add static lifecycle twice: {}",
                                      p_Lifecycle->m_Info.Name);
            }
            else {
                m_Lifecycles.push_back(p_Lifecycle);
                m_Statics[p_Lifecycle->GetTypeId()] = p_Lifecycle;
                m_Dirty = true;
            }
        }
        else {
            if (auto it =
                    std::find(m_Lifecycles.begin(), m_Lifecycles.end(), p_Lifecycle);
                it != m_Lifecycles.end()) {
                ENGINE_CORE_DEV_ERROR("Try to add lifecycle pointer twice: {}",
                                      p_Lifecycle->m_Info.Name);
            }
            else {
                m_Lifecycles.push_back(p_Lifecycle);
                m_Dirty = true;
            }
        }
    }

    void LifecycleManager::Pop(Lifecycle<LifecycleObject>* p_Lifecycle)
    {
        if (p_Lifecycle->m_Info.Static) {
            if (auto it = m_Statics.find(p_Lifecycle->GetTypeId());
                it != m_Statics.end()) {
                if (auto it2 =
                        std::find(m_Lifecycles.begin(), m_Lifecycles.end(), p_Lifecycle);
                    it2 != m_Lifecycles.end()) {
                    m_Lifecycles.erase(it2);
                }
                m_Statics.erase(p_Lifecycle->GetTypeId());
                m_Dirty = true;
            }
            else {
                ENGINE_CORE_DEV_ERROR("Failed to pop lifecycle: {}",
                                      p_Lifecycle->m_Info.Name);
            }
        }
        else {
        }
    }

    void LifecycleManager::Order()
    {
        std::vector<Engine::Node*> nodes;

        for (const auto lifecycle : m_Lifecycles) {
            lifecycle->m_InNeighbours.clear();
            lifecycle->m_OutNeighbours.clear();
        }

        for (auto* lifecycle : m_Lifecycles) {
            for (auto* dependency : lifecycle->m_Info.Dependencies) {
                dependency->m_OutNeighbours.push_back(lifecycle);
                lifecycle->m_InNeighbours.push_back(dependency);
            }

            nodes.push_back(lifecycle);
        }

        Graph graph(nodes);
        graph.SortDependencies();

        nodes = graph.GetSortedNodes();
        m_Functions.clear();
        std::reverse(nodes.begin(), nodes.end());

        for (const auto& node : nodes) {
            auto lifecycle = static_cast<Lifecycle<LifecycleObject>*>(node);
            for (const auto& [stage, function] : lifecycle->m_Info.Functions) {
                m_Functions.insert(std::pair(stage, function));
            }
        }

        m_Dirty = false;
    }

    void LifecycleManager::CallState(LifecycleState p_State)
    {
        if (m_Dirty) {
            Order();
        }

        for (auto it = m_Functions.find(p_State); it != m_Functions.end(); it++) {
            it->second();
        }
    }
} // namespace Engine