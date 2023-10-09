#include "PointLayer.h"

#include "j2me/Image.h"
#include <iostream>

namespace arkanerd {
	PointLayer::PointLayer(int digits)
    : j2me::TiledLayer(digits, 1, j2me::Image::createImage("/images/font.png"), 16, 16)
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
/*
void PointLayer::add(int amount) {
  std::cerr << "ADD\n";
  number_ += amount;
  text_ = std::to_string(number_);
  for (int i = 0; i < digits_; i++) {
    setCell(i, 0, chars_.find(text_.substr(i, 1)) + 1);
  }
}
*/
} // namespace arkanerd

