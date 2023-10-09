#include "Sprite.h"
#include "Graphics.h"
#include "Image.h"
#include "TiledLayer.h"

#include <cstdlib>

namespace j2me {

Sprite::Sprite(const j2me::Image& img)
  : Layer(img.getWidth(), img.getHeight())
  , images_({img})
  , frame_(images_.begin()) {
}

Sprite::Sprite(const j2me::Image& img, int frameWidth, int frameHeight)
  : Layer(frameWidth, frameHeight) {
  for (int y = 0; y < img.getHeight(); y += frameHeight) {
    for (int x = 0; x < img.getWidth(); x += frameWidth) {
      images_.push_back(Image::createImage(img, x, y, frameWidth, frameHeight, 0));
    }
  }
  frame_ = images_.begin();
}

void Sprite::paint(Graphics* g) {
  if (!images_.empty()) {
    g->drawImage(*frame_, getX(), getY(), Graphics::LEFT | Graphics::TOP);
  }
}

void Sprite::clear() {
}

bool Sprite::collidesWith(TiledLayer* t, bool /*pixelLevel*/) {
  sf::Rect bounds{getX(), getY(), getWidth(), getHeight()};
  if (bounds.intersects(sf::Rect{t->getX(), t->getY(), t->getWidth(), t->getHeight()})) {
    return true;
  }
  return false;
}

bool Sprite::collidesWith(Sprite* t, bool /*pixelLevel*/) {
  sf::Rect bounds{getX(), getY(), getWidth(), getHeight()};
  if (bounds.intersects(sf::Rect{t->getX(), t->getY(), t->getWidth(), t->getHeight()})) {
    return true;
  }
  return false;
}

void Sprite::nextFrame() {
  if (++frame_ == images_.end()) {
    frame_ = images_.begin();
  }
}

} // namespace j2me
