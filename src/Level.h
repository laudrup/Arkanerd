#pragma once

#include "Brick.h"

#include <memory>
#include <string>
#include <vector>

/*
  Level.java

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
	class Level {
  public:
    Level(const Level &) = default;
    Level(Level &&) = default;
    Level &operator=(const Level &) = default;
    Level &operator=(Level &&) = default;
    Level(int num);

    // Number of bricks _excluding_ empty (Actual number of images in this level)
    int getNumBricks() const;
		// Number of rows _including_ empty
		int getBricks_x() const;
		// Number of lines _including_ empty
		int getBricks_y() const;
		std::string getName() const;

		bool isEmpty(int i) const;
		std::vector<Brick> getBricks() const;

	private:
		int bricks_x_ = 0;
    int bricks_y_ = 0;
    int num_bricks_ = 0;
		std::vector<Brick> bricks_;
		std::string name_;
		std::vector<bool> empty_;

	private:
		void parseLevelFile(const std::vector<std::string>& lines);
		std::vector<std::string> readFile(const std::string& fname);
	};

} // namespace arkanerd

