#include "BonusBrick.h"

#include "j2me/Image.h"

namespace arkanerd {

BonusBrick::BonusBrick(ResourceManager& resources, int type)
  : j2me::Sprite(j2me::Image::createImage(resources.getTexture("/images/bonus" + std::to_string(type) + ".png")), 20, 10)
  , type_(type) {
}

int BonusBrick::getType() {
  return type_;
}

} // namespace arkanerd
