#pragma once

#include "ResourceManager.h"

#include "j2me/Sprite.h"

namespace arkanerd {

class Board : public j2me::Sprite {
public:
  Board(ResourceManager& resources);
};

} // namespace arkanerd
