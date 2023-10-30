#include "Brick.h"

#include "j2me/Image.h"

namespace arkanerd {

Brick::Brick(ResourceManager& resources, int color, int type)
  : j2me::Sprite(j2me::Image::createImage(resources.getTexture("/images/brick" + std::to_string(color) + ".png")))
  , type_(type) {
}

int Brick::getType() {
  return type_;
}

} // namespace arkanerd
