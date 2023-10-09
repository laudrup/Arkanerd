#pragma once

#include "Player.h"

#include <iosfwd>
#include <string>

namespace j2me {
class Manager {
public:
  static Player createPlayer(std::istream& stream, const std::string& type);
};
} // namespace j2me
