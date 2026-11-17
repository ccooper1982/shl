
#include <filesystem>
#include <shl/exec/file.hpp>
#include <shl/functional.hpp>

#include <fstream>

namespace file
{
  /// Create the file, including parent directories.
  VarValue file_create(RuntimeContext& rc, const std::span<const VarValue> args)
  {
    const fs::path path {std::get<ShlString>(args[0])};

    if (std::error_code ec; path.has_parent_path())
    {
      if (fs::create_directories(path.parent_path(), ec); ec)
      {
        rc.err_code = ec;
        return false;
      }
    }

    std::ofstream file {path, std::ios::app};
    if (!file.is_open()) {
      rc.err_code = std::error_code(errno, std::generic_category());
    }
    return file.is_open();
  }

  VarValue dir_create(RuntimeContext& rc, const std::span<const VarValue> args)
  {
    const fs::path path {std::get<ShlString>(args[0])};

    fs::create_directories(path, rc.err_code);
    return !rc.err_code;
  }

  VarValue path_exists(RuntimeContext& rc, const std::span<const VarValue> args)
  {
    const fs::path path {std::get<ShlString>(args[0])};

    rc.err_code.clear();
    return !rc.err_code && fs::exists(path, rc.err_code);
  }

  VarValue path_rmv(RuntimeContext& rc, const std::span<const VarValue> args)
  {
    fs::remove(std::get<ShlString>(args[0]), rc.err_code);
    return !rc.err_code;
  }

  VarValue path_rmv_dir(RuntimeContext& rc, const std::span<const VarValue> args)
  {
    fs::remove_all(std::get<ShlString>(args[0]), rc.err_code);
    return !rc.err_code;
  }
}
