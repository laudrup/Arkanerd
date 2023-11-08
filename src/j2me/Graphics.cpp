#include "Graphics.h"

#include <cassert>
#include <cmath>
#include <iostream>

namespace j2me {
Graphics::Graphics(sf::RenderTarget* target)
  : target_(target) {
}

void Graphics::drawImage(const Image& img, int x, int y, [[maybe_unused]] int anchor) {
  auto sprite = img.sprite();
  sprite->setPosition(static_cast<float>(x), static_cast<float>(y));
  target_->draw(*sprite);
  drawables_.push_back(std::move(sprite));
}

sf::RenderTarget* Graphics::target() const {
  return target_;
}

} // namespace j2me
