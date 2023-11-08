#include "Settings.h"

#include "os_util.h"

#include <cstdlib>
#include <fstream>

namespace arkanerd {

Settings::Settings()
  : data_dir_(data_dir() / "arkanerd") {
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
