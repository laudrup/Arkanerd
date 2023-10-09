
#include "Image.h"
#include "Sprite.h"

#include <cassert>
#include <string>

namespace j2me {
Image::Image(const std::string& path) {
  std::string full_path{std::string{"../res/"} + path};
  if (!texture_.loadFromFile(full_path)) {
    throw std::runtime_error{std::string{"Unable to load: "} + full_path};
  }
}

Image::Image(const sf::Image& img, const sf::IntRect& area) {
  if (!texture_.loadFromImage(img, area)) {
    throw std::runtime_error{"Unable to load image"};
  }
}

Image Image::createImage(const std::string& path) {
  return Image{path};
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
