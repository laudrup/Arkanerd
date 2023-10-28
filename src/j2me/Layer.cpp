#include "Layer.h"

#include <cstdlib>

namespace j2me {

Layer::Layer(int width, int height)
  : width_(width)
  , height_(height) {
}

int Layer::getHeight() const {
  return height_;
}

int Layer::getWidth() const {
  return width_;
}

void Layer::setPosition(int x, int y) {
  x_ = x;
  y_ = y;
}

int Layer::getX() {
  return x_;
}

int Layer::getY() {
  return y_;
}

void Layer::move(int dx, int dy) {
  x_ += dx;
  y_ += dy;
}

/*
void Layer::setVisible(bool visible) {
  visible_ = visible;
}

bool Layer::visible() const {
  return visible_;
}
*/

} // namespace j2me
