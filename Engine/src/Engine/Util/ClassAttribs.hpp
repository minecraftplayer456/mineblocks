#pragma once

class NonCopyable {
  protected:
    NonCopyable() = default;
    virtual ~NonCopyable() = default;

  public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) noexcept = default;
    auto operator=(const NonCopyable&) -> NonCopyable& = delete;
    auto operator=(NonCopyable&&) noexcept -> NonCopyable& = default;
};

class NonMovable {
  protected:
    NonMovable() = default;
    virtual ~NonMovable() = default;

  public:
    NonMovable(const NonMovable&) = default;
    NonMovable(NonMovable&&) noexcept = delete;
    auto operator=(const NonMovable&) -> NonMovable& = default;
    auto operator=(NonMovable&&) noexcept -> NonMovable& = delete;
};

class NonCopyMovable {
  protected:
    NonCopyMovable() = default;
    virtual ~NonCopyMovable() = default;

  public:
    NonCopyMovable(const NonCopyMovable&) = delete;
    NonCopyMovable(NonCopyMovable&&) noexcept = delete;
    auto operator=(const NonCopyMovable&) -> NonCopyMovable& = delete;
    auto operator=(NonCopyMovable&&) noexcept -> NonCopyMovable& = delete;
};