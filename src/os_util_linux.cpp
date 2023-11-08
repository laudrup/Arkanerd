#include "os_util.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

namespace arkanerd {

std::filesystem::path current_exe_path() {
  return std::filesystem::read_symlink("/proc/self/exe").parent_path();
}

std::filesystem::path data_dir() {
  if (const char* dir = getenv("XDG_DATA_HOME"); dir != nullptr) {
    return std::filesystem::path{dir};
  }
  const auto home = getpwuid(getuid())->pw_dir;
  return std::filesystem::path{home} / ".local" / "share";
}

} // namespace arkanerd
