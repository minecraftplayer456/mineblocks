#pragma once

#ifdef _WIN32
#ifdef _WIN64
#define ENGINE_PLATFORM_WINDOWS
#else
#error "Windows x86 is not supported"
#endif
#elif
#error "Only windows 64x is supported"
#endif

constexpr auto Bit(int x) -> int
{
    return 1 << x;
}