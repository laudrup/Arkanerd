#pragma once

#include <filesystem>

namespace arkanerd {

std::filesystem::path current_exe_path();
std::filesystem::path data_dir();

} // namespace arkanerd
