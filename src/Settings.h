#pragma once

#include <filesystem>
#include <string>
#include <vector>

/*
  Settings.java

  Arkanerd - An Arkanoid/Breakout like game for J2ME mobile phones
  Copyright (C) 2006  Kasper Laudrup

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

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
