#pragma once

#include "Engine/Core/Engine.hpp"

extern Engine::Application* Engine::CreateApplication();

/*
class TestEvent : public Engine::Event<TestEvent> {
  public:
    [[nodiscard]] const char* GetName() const override;

    [[nodiscard]] Engine::ModuleStage GetCallStage() const override;
};

class TestEvent2 : public Engine::Event<TestEvent2> {
  public:
    [[nodiscard]] const char* GetName() const override;

    [[nodiscard]] Engine::ModuleStage GetCallStage() const override;
};

class TestEventHandler : public Engine::EventHandler<TestEvent> {
  public:
    bool Handle(const TestEvent& p_Event) override;
};

class TestEventHandler2 : public Engine::EventHandler<TestEvent2> {
  public:
    bool Handle(const TestEvent2& p_Event) override;
};*/
