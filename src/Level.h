#pragma once

#include "Brick.h"

#include <memory>
#include <string>
#include <vector>

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

