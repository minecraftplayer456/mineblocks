auto main() -> int
{
#ifdef CONFIGURATION_DEBUG
    std::cout << "Debug" << std::endl;
#elif CONFIGURATION_RELEASE
    std::cout << "Release" << std::endl;
#elif CONFIGURATION_DIST
    std::cout << "Dist" << std::endl;
#else
#error Unknown configuration
#endif
}