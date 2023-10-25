#pragma once

#include "j2me/Sprite.h"

#include <string>

namespace arkanerd {
class Board : public j2me::Sprite {
public:
  Board();

private:
  static std::string BOARD_FILE;
};

} // namespace arkanerd
