#pragma once

#include <cctype>
#include <expected>
#include <filesystem>
#include <string_view>
#include <ranges>

namespace fs = std::filesystem;
namespace rg = std::ranges;
namespace vw = std::views;


// helper type for the visiting
template<class... Ts>
struct overloads : Ts... { using Ts::operator()...; };

struct SourceFile;
class Issues;

struct Script
{
  std::unique_ptr<std::string> src{};
  std::unique_ptr<SourceFile> ast{};
  std::unique_ptr<Issues> issues{};
  fs::path file{};
};


struct SourceRegion
{
  SourceRegion() = default;
  SourceRegion(const uint32_t from, const uint32_t to)
    : start(from)
    , end(to)
  {
  }

  uint32_t start{}, end{};
};

struct ShlError
{
  ShlError() = default;

  ShlError(const std::string_view msg) : m_msg(msg)
  {}

  bool operator()() const
  {
    return !m_msg.empty();
  }

  const std::string& msg() const
  {
    return m_msg;
  }

private:
  std::string m_msg;
};

template<typename Expected>
std::expected<Expected, ShlError> make_error(const std::string_view msg)
{
  return std::unexpected(ShlError{msg});
}

inline std::string_view trim_ws(std::string_view str)
{
  while (!str.empty() && std::isspace(static_cast<unsigned char>(str.back()))) {
    str.remove_suffix(1);
  }

  return str;
}
