#pragma once

namespace Engine {
    using TypeId = std::size_t;

    template <typename T>
    class TypeInfo {
      public:
        TypeInfo() = delete;

        template <typename K,
                  typename = std::enable_if<std::is_convertible<K*, T*>::value>>
        static TypeId GetTypeId() noexcept
        {
            std::type_index typeIndex(typeid(K));
            if (auto it = s_TypeMap.find(typeIndex); it != s_TypeMap.end()) {
                return it->second;
            }

            const auto id = NextTypeId();
            s_TypeMap[typeIndex] = id;
            return id;
        }

      private:
        static TypeId s_NextTypeId;
        static std::unordered_map<std::type_index, TypeId> s_TypeMap;

        static TypeId NextTypeId() noexcept
        {
            const auto id = s_NextTypeId;
            ++s_NextTypeId;
            return id;
        }
    };

    template <typename T, typename K>
    class TypeObject {
      public:
        TypeObject();

        [[nodiscard]] TypeId GetTypeId() const;

      private:
        TypeId m_TypeId = -1;
    };

    template <typename T, typename K>
    TypeObject<T, K>::TypeObject()
    {
        m_TypeId = TypeInfo<T>::template GetTypeId<K>();
    }

    template <typename T, typename K>
    TypeId TypeObject<T, K>::GetTypeId() const
    {
        return m_TypeId;
    }

    template <typename K>
    TypeId TypeInfo<K>::s_NextTypeId = 0;

    template <typename K>
    std::unordered_map<std::type_index, TypeId> TypeInfo<K>::s_TypeMap = {};
} // namespace Engine