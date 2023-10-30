
#include "Image.h"
#include "Sprite.h"

#include <cassert>
#include <string>

namespace j2me {
Image::Image(const sf::Texture* texture)
  : texture_(*texture) {
}

Image::Image(const sf::Image& img, const sf::IntRect& area) {
  if (!texture_.loadFromImage(img, area)) {
    throw std::runtime_error{"Unable to load image"};
  }
}

Image Image::createImage(const sf::Texture* texture) {
  return Image{texture};
}

Image Image::createImage(const Image& image, int x, int y, int width, int height, [[maybe_unused]] int transform) {
  assert(transform == j2me::Sprite::TRANS_NONE);
  return Image{image.texture_.copyToImage(), sf::IntRect{x, y, width - 1, height - 1 }};
}

int Image::getWidth() const {
  return texture_.getSize().x;
}

int Image::getHeight() const {
  return texture_.getSize().y;
}

std::unique_ptr<sf::Sprite> Image::sprite() const {
  return std::make_unique<sf::Sprite>(texture_);
}

} // namespace j2me
