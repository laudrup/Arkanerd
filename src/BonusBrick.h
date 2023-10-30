#pragma once

#include "ResourceManager.h"

#include "j2me/Sprite.h"

namespace arkanerd {
class BonusBrick : public j2me::Sprite {
public:
  BonusBrick(ResourceManager& resources, int type);
  int getType();

  static constexpr int NO_BONUS = 0;
  static constexpr int POINT_BONUS = 1;
  static constexpr int STICKY_BONUS = 2;
  static constexpr int BREAK_BONUS = 3;
  static constexpr int LIVE_BONUS = 4;

private:
  int type_ = 0;
};

} // namespace arkanerd

