#pragma once

#include <shl/common.hpp>
#include <shl/functional.hpp>


namespace core
{
  // output
  VarValue print(RuntimeContext&, const std::span<const VarValue> args);
  VarValue println(RuntimeContext& ctx, const std::span<const VarValue> args);

  VarValue exit(RuntimeContext&, const std::span<const VarValue> args);

  // errors
  VarValue error_code(RuntimeContext& rc, const std::span<const VarValue>);
  VarValue error_message(RuntimeContext& rc, const std::span<const VarValue>);

  // env
  VarValue env(RuntimeContext&, const std::span<const VarValue> args);
  VarValue env_set(RuntimeContext&, const std::span<const VarValue> args);
  VarValue env_exists(RuntimeContext&, const std::span<const VarValue> args);
  VarValue home(RuntimeContext&, const std::span<const VarValue>);

  VarValue to_int(RuntimeContext&, const std::span<const VarValue> args);
  VarValue to_dec(RuntimeContext&, const std::span<const VarValue> args);
  VarValue to_bool(RuntimeContext&, const std::span<const VarValue> args);
  VarValue to_str(RuntimeContext&, const std::span<const VarValue> args);

  // argv //
  size_t get_argv_index(RuntimeContext& ctx, const std::span<const VarValue> args);
  VarValue get_argv_str(RuntimeContext& ctx, const std::span<const VarValue> args);
  VarValue get_argv_int(RuntimeContext& ctx, const std::span<const VarValue> args);
  VarValue get_argv_dec(RuntimeContext& ctx, const std::span<const VarValue> args);
  VarValue get_argv_bool(RuntimeContext& ctx, const std::span<const VarValue> args);
  VarValue get_argc(RuntimeContext& ctx, const std::span<const VarValue> args);
}


inline const std::map<std::string_view, NativeFunctionDef> NativeCoreFunctions
{
  create_function<core::print>("print", {}, NativeType::Void, ParamMode::VariadicAny),
  create_function<core::println>("println", {}, NativeType::Void, ParamMode::VariadicAny),

  create_function<core::exit>("exit", {{"status", NativeType::Int}}, NativeType::Void, ParamMode::Fixed),

  // error
  create_function<core::error_code>("error_code", {}, NativeType::Int, ParamMode::Fixed),
  create_function<core::error_message>("error_message", {}, NativeType::String, ParamMode::Fixed),

  // environment
  create_function<core::home>("home", {}, NativeType::String, ParamMode::Fixed),
  create_function<core::env>("env", {{"name", NativeType::String}}, NativeType::String, ParamMode::Fixed),
  create_function<core::env_set>("env_set", {{"name", NativeType::String},{"value", NativeType::String}}, NativeType::Void, ParamMode::Fixed),
  create_function<core::env_exists>("env_exists", {{"name", NativeType::String}}, NativeType::Bool, ParamMode::Fixed),

  // conversion
  // TODO max_args = 1
  create_function<core::to_int>("to_int", {}, NativeType::Int, ParamMode::VariadicAny, 1),
  create_function<core::to_dec>("to_dec", {}, NativeType::Decimal, ParamMode::VariadicAny, 1),
  create_function<core::to_bool>("to_bool", {}, NativeType::Bool, ParamMode::VariadicAny, 1),
  create_function<core::to_str>("to_str", {}, NativeType::String, ParamMode::VariadicAny, 1),

  // argv
  create_function<core::get_argc>("arg_count", {}, NativeType::Int, ParamMode::Fixed),
  create_function<core::get_argv_str>("arg_str", {{"index", NativeType::Int}}, NativeType::String, ParamMode::Fixed),
  create_function<core::get_argv_int>("arg_int", {{"index", NativeType::Int}}, NativeType::Int, ParamMode::Fixed),
  create_function<core::get_argv_dec>("arg_dec", {{"index", NativeType::Int}}, NativeType::Decimal, ParamMode::Fixed),
  create_function<core::get_argv_bool>("arg_bool", {{"index", NativeType::Int}}, NativeType::Bool, ParamMode::Fixed)
};
