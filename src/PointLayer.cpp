#include "PointLayer.h"

namespace arkanerd {
PointLayer::PointLayer(ResourceManager& resources, int digits)
  : j2me::TiledLayer(resources.getTexture("/images/font.png"), digits, 1, 16, 16)
  , digits_(digits) {
  for (int i = 0; i < digits; i++) {
    setCell(i, 0, static_cast<int>(chars_.find("0")) + 1);
  }
}

void PointLayer::setNum(int num) {
  number_ = num;
  text_ = std::to_string(number_);
  for (int i = 0; i < static_cast<int>(text_.length()); i++) {
    setCell(digits_ - static_cast<int>(text_.length()) + i, 0, static_cast<int>(chars_.find(text_.substr(i, 1))) + 1);
  }
}

} // namespace arkanerd
