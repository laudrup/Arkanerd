#include "Level.h"
#include "Brick.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace arkanerd {

Level::Level(int num) {
  std::vector lines = readFile("../res/levels/level" + std::to_string(num) + ".txt");
  parseLevelFile(lines);
}

int Level::getNumBricks() const {
  return num_bricks_;
}

int Level::getBricks_x() const {
  return bricks_x_;
}

int Level::getBricks_y() const {
  return bricks_y_;
}

std::string Level::getName() const {
  return name_;
}

bool Level::isEmpty(int i) const {
  return empty_[i];
}


std::vector<Brick> Level::getBricks() const {
  return bricks_;
}

void Level::parseLevelFile(const std::vector<std::string>& lines) {
  int color, type;
  int count = 0;
  for (const auto& line : lines) {
    if (line.rfind("#") == 0) {
      continue; // Skip comments
    }
    else if (line.rfind("Name") == 0) {
      name_ = line.substr(5);
    } else {
      // The definition of a brick is 2 chars
      bricks_x_ = static_cast<int>(line.length()) / 2;
      bricks_y_++;
    }
  }
  // Then get the brick definitions
  empty_ = std::vector<bool>(bricks_x_ * bricks_y_);
  for (const auto& line : lines) {
    if ((line.rfind("#") == 0) || (line.rfind("Name") == 0)) {
      continue;
    } else {
      for (size_t i = 0; i < line.length(); i += 2) {
        color = std::stoi(line.substr(i, 1));
        type = std::stoi(line.substr(i + 1, (i + 2) - (i + 1)));
        if (color == 0) {
          empty_[count] = true;
        } else {
          //brick = new Brick(color, type);
          bricks_.push_back(Brick(color, type));
          num_bricks_++;
        }
        count++;
      }
    }
  }
}

std::vector<std::string> Level::readFile(const std::string& fname) {
  std::vector<std::string> ret;
  std::ifstream ifs{fname};
  if (!ifs.is_open()) {
    throw std::runtime_error("Unable to open: " + fname);
  }
  std::string line;
  while (std::getline(ifs, line)) {
    ret.push_back(line);
  }
  return ret;
}

} // namespace arkanerd
