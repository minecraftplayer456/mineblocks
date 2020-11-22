#pragma once

namespace Engine {
    using TypeId = std::size_t;

    template <typename T>
    class TypeInfo {
      public:
        TypeInfo() = delete;

        template <typename K,
                  typename = std::enable_if<std::is_convertible<K*, T*>::value>>
        static auto GetTypeId() noexcept -> TypeId
        {
            std::type_index typeIndex(typeid(K));
            if (auto it = typeMap.find(typeIndex); it != typeMap.end()) {
                return it->second;
            }

            const auto id = NextTypeId();
            typeMap[typeIndex] = id;
            return id;
        }

      private:
        static TypeId nextTypeId;
        static std::unordered_map<std::type_index, TypeId> typeMap;

        static auto NextTypeId() noexcept -> TypeId
        {
            const auto id = nextTypeId;
            ++nextTypeId;
            return id;
        }
    };

    template <typename K>
    TypeId TypeInfo<K>::nextTypeId = 0;

    template <typename K>
    std::unordered_map<std::type_index, TypeId> TypeInfo<K>::typeMap = {};
} // namespace Engine