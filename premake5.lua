require "cmake"
require "build/conanbuildinfo.premake"

workspace "Mineblocks"
  configurations { "Debug", "Release", "Dist" }
  platforms { "Win64" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Mineblocks"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  includedirs { conan_includedirs }
  libdirs { conan_libdirs }
  links { conan_links }
  linkoptions { conan_linkoptions }
  defines { conan_cppdefines, "GLFW_INCLUDE_NONE" }

  pchheader "src/Pch.hpp"
  pchsource "src/Pch.cpp"

  files { "src/**.hpp", "src/**.cpp", "src/**.h", "src/**.c" }

  filter "configurations:Debug"
    defines { "CONFIGURATION_DEBUG" }
    symbols "on"

  filter "configurations:Release"
    defines { "CONFIGURATION_RELEASE" }
    optimize "on"

  filter "configurations:Dist"
    defines { "CONFIGURATION_DIST" }
    optimize "on"

  filter "platforms:Win64"
    system "Windows"
    architecture "x86_64"