#pragma once

#include <typeindex>
#include <unordered_map>

namespace engine::utils {
    using TypeId = std::size_t;

    template <typename T>
    class TypeInfo {
      public:
        TypeInfo() = delete;

        template <typename K, typename = std::enable_if<std::is_convertible_v<K*, T*>>>
        static TypeId getTypeId() noexcept
        {
            std::type_index typeIndex(typeid(K));

            for (auto it = m_typeMap.find(typeIndex); it != m_typeMap.end();) {
                return it->second;
            }

            const auto id = nextTypeId();
            m_typeMap[typeIndex] = id;
            return id;
        }

      private:
        static TypeId nextTypeId() noexcept
        {
            const auto id = m_nextTypeId;
            m_nextTypeId++;
            return id;
        }

        static TypeId m_nextTypeId;
        static std::unordered_map<std::type_index, TypeId> m_typeMap;
    };

    template <typename K>
    TypeId TypeInfo<K>::m_nextTypeId = 0;

    template <typename K>
    std::unordered_map<std::type_index, TypeId> TypeInfo<K>::m_typeMap = {};
} // namespace engine::utils