#pragma once

#include <shl/functional.hpp>

namespace file
{
  VarValue file_create(RuntimeContext& rc, const std::span<const VarValue> args);
  VarValue dir_create(RuntimeContext& rc, const std::span<const VarValue> args);
  VarValue path_exists(RuntimeContext& rc, const std::span<const VarValue> args);
}


inline const std::map<std::string_view, NativeFunctionDef> NativeFileFunctions
{
  create_function<file::file_create>("file_create", {{"path", NativeType::String}}, NativeType::Bool, ParamMode::Fixed),
  create_function<file::dir_create>("dir_create", {{"path", NativeType::String}}, NativeType::Bool, ParamMode::Fixed),
  create_function<file::path_exists>("path_exists", {{"path", NativeType::String}}, NativeType::Bool, ParamMode::Fixed),
};
