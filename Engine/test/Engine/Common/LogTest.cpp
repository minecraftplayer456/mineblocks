TEST(logTest, logInitializationTest)
{
    ASSERT_TRUE(Engine::Log::Initialize());
}

TEST(logTest, logConsoleTest)
{
    Engine::Log::Initialize();

    ENGINE_CORE_TRACE("Trace");
    ENGINE_CORE_DEBUG("Debug");
    ENGINE_CORE_INFO("Info");
    ENGINE_CORE_WARN("Warn");
    ENGINE_CORE_ERROR("Error");
    ENGINE_CORE_CRITICAL("Critical");
}