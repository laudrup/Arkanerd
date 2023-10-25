#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace arkanerd {
class Settings {

public:
  Settings();
  void setHighScore(int h);
  int getHighScore();
  void setMusic(bool b);
  bool musicOn();

private:
  std::filesystem::path data_dir_;
  bool music_on_ = false;
};

} // namespace arkanerd
