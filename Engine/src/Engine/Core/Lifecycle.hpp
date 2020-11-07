#pragma once

#include <utility>

#include "Engine/Util/Graph.hpp"
#include "Engine/Util/TypeInfo.hpp"

namespace Engine {
    template <typename T>
    class Lifecycle;

    class LifecycleManager;

    enum class LifecycleState { Init, Input, Update, Render, Cleanup };

    using LifecycleFunc = std::function<void()>;

    class LifecycleObject {
    };

    struct LifecycleInfo {
      public:
        const char* Name;
        bool Static = false;
        std::unordered_map<LifecycleState, LifecycleFunc> Functions;
        std::vector<Lifecycle<LifecycleObject>*> Dependencies;
    };

    template <typename T>
    class Lifecycle : public LifecycleObject,
                      public TypeObject<LifecycleObject, T>,
                      private Node {
        friend LifecycleManager;

      protected:
        LifecycleInfo m_Info;
    };

    class LifecycleManager {
      public:
        ~LifecycleManager();

        void Push(Lifecycle<LifecycleObject>* p_Lifecycle);
        void Pop(Lifecycle<LifecycleObject>* p_Lifecycle);

        template <typename T, typename... Args>
        T* Push(Args... args);
        template <typename T>
        T* Pop();

        void Order();

        void CallState(LifecycleState p_State);

      private:
        bool m_Dirty = false;

        std::vector<Lifecycle<LifecycleObject>*> m_Lifecycles;
        std::unordered_map<TypeId, Lifecycle<LifecycleObject>*> m_Statics;
        std::unordered_multimap<LifecycleState, LifecycleFunc> m_Functions;
    };

    template <typename T, typename... Args>
    T* LifecycleManager::Push(Args... args)
    {
        auto typeId = TypeInfo<LifecycleObject>::GetTypeId<T>();
        if (auto it = m_Statics.find(typeId); it != m_Statics.end()) {
            ENGINE_CORE_ERROR("Try to add static lifecycle twice typeid: {}", typeId);
        }
        else {
            auto* lifecycle =
                reinterpret_cast<Lifecycle<LifecycleObject>*>(new T(args...));
            if (lifecycle->m_Info.Static) {
                m_Statics[typeId] = lifecycle;
                m_Lifecycles.push_back(lifecycle);
                m_Dirty = true;
            }
            else {
                m_Lifecycles.push_back(lifecycle);
                m_Dirty = true;
            }
            return reinterpret_cast<T*>(lifecycle);
        }
        return nullptr;
    }

    template <typename T>
    T* LifecycleManager::Pop()
    {
        auto typeId = TypeInfo<LifecycleObject>::GetTypeId<T>();
        if (auto it = m_Statics.find(typeId); it != m_Statics.end()) {
            auto* lifecycle = m_Statics[typeId];
            if (auto it2 = std::find(m_Lifecycles.begin(), m_Lifecycles.end(), lifecycle);
                it2 != m_Lifecycles.end()) {
                m_Lifecycles.erase(it2);
            }
            m_Statics.erase(typeId);
            m_Dirty = true;
            return lifecycle;
        }
        else {
            auto it2 = std::find_if(m_Lifecycles.begin(), m_Lifecycles.end(),
                                    [typeId](const Lifecycle<LifecycleObject>* l) {
                                        return l->GetTypeId() == typeId;
                                    });
            if (it2 != m_Lifecycles.end()) {
                for (; it2 != m_Lifecycles.end(); it2++) {
                    m_Lifecycles.erase(it2);
                }
                m_Dirty = true;
            }
        }
    }
} // namespace Engine
