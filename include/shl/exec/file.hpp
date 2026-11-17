#pragma once

#include <shl/functional.hpp>

namespace file
{
  VarValue file_create(RuntimeContext& rc, const std::span<const VarValue> args);
  VarValue dir_create(RuntimeContext& rc, const std::span<const VarValue> args);

  VarValue path_rmv(RuntimeContext& rc, const std::span<const VarValue> args);
  VarValue path_rmv_dir(RuntimeContext& rc, const std::span<const VarValue> args);
  VarValue path_exists(RuntimeContext& rc, const std::span<const VarValue> args);
  VarValue path_is_file(RuntimeContext& rc, const std::span<const VarValue> args);
  VarValue path_is_dir(RuntimeContext& rc, const std::span<const VarValue> args);
}


inline const std::map<std::string_view, NativeFunctionDef> NativeFileFunctions
{
  // create
  create_function<file::file_create>("file_create", {{"path", NativeType::String}}, NativeType::Bool),
  create_function<file::dir_create>("dir_create", {{"path", NativeType::String}}, NativeType::Bool),

  // path
  create_function<file::path_rmv>("path_rmv", {{"path", NativeType::String}}, NativeType::Bool),
  create_function<file::path_rmv_dir>("path_rmv_dir", {{"path", NativeType::String}}, NativeType::Bool),
  create_function<file::path_exists>("path_exists", {{"path", NativeType::String}}, NativeType::Bool),
  create_function<file::path_is_file>("path_is_file", {{"path", NativeType::String}}, NativeType::Bool),
  create_function<file::path_is_dir>("path_is_dir", {{"path", NativeType::String}}, NativeType::Bool),
};
