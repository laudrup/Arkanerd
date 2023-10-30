#pragma once

#include "ResourceManager.h"

#include "j2me/Sprite.h"

namespace arkanerd {

class Brick : public j2me::Sprite {
public:
  Brick() = default;
  Brick(ResourceManager& resources, int color, int type);
  int getType();
		//public static final int BLUE = 1;
		//public static final int GREEN = 2;
		//public static final int PURPLE = 3;
		//public static final int BONUS = 10;
		//private static Image image;
		//public static final int BONUS = 1;
private:
  int type_ = 0;
};

} // namespace arkanerd
