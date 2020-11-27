add_library(Engine
        src/Engine/Core/Application.cpp
        src/Engine/Core/Engine.cpp
        src/Engine/Core/EntryPoint.cpp
        src/Engine/Core/Event.cpp
        src/Engine/Core/Log.cpp
        src/Engine/Core/Module.cpp

        src/Engine/Devices/Windows.cpp

        src/Engine/Maths/Time.cpp

        src/Engine/Util/ClassAttribs.hpp
        src/Engine/Util/Graph.cpp
        src/Engine/Util/Singleton.hpp
        src/Engine/Util/TypeInfo.hpp
        src/Engine/Util/Version.cpp

        src/Platform/Windows/WindowsWindow.cpp

        src/Engine.hpp
        )

target_include_directories(Engine PUBLIC src/)

target_precompile_headers(Engine PUBLIC src/enginepch.hpp)

target_link_libraries(Engine ${CONAN_LIBS})