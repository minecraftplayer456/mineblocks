#pragma once

class TestBase :public ::testing::Test{
  protected:
    TestBase()= default;
    ~TestBase() override= default;

    static void SetUpTestSuite(){
        Engine::Log::Initialize();
    };
};
