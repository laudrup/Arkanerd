#include "Settings.h"

#include <cstdlib>
#include <fstream>

#if !defined(WIN32)
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

namespace {
std::filesystem::path get_data_dir() {
#ifdef WIN32
  return {};
#else
  if (const char* dir = getenv("XDG_DATA_HOME"); dir != nullptr) {
    return std::filesystem::path{dir};
  }
  const auto home = getpwuid(getuid())->pw_dir;
  return std::filesystem::path{home} / ".local" / "share";
#endif
}
} // namespace

namespace arkanerd {

Settings::Settings()
  : data_dir_(get_data_dir() / "arkanerd") {
  std::filesystem::create_directories(data_dir_);
}

void Settings::setHighScore(int h) {
  std::ofstream ofs(data_dir_ / "highscore", std::ios::trunc);
  ofs << h;
}

int Settings::getHighScore() {
  std::ifstream ifs(data_dir_ / "highscore");
  int high_score = 0;
  ifs >> high_score;
  return high_score;
}

void Settings::setMusic(bool b) {
  music_on_ = b;
}

bool Settings::musicOn() {
  return music_on_;
}

} // namespace arkanerd
