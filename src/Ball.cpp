#include "Ball.h"
#include "ArkanerdCanvas.h"

#include "j2me/Image.h"

namespace arkanerd {

Ball::Ball(ResourceManager& resources, ArkanerdCanvas* canvas)
  : j2me::Sprite(j2me::Image::createImage(resources.getTexture("/images/ball.png")))
  , canvas_(canvas) {
  width = canvas_->getWidth();
  sticky = true;
}

void Ball::setSticky(bool b) {
  sticky = b;
}

bool Ball::isSticky() {
  return sticky;
}

void Ball::setAngle(int x_angle, int y_angle) {
  x_dir = x_angle;
  y_dir = y_angle;
}

void Ball::reverseX() {
  x_dir = -x_dir;
}

void Ball::reverseY() {
  y_dir = -y_dir;
}

void Ball::update() {
  if (getX() >= width - ArkanerdCanvas::FRAME_WIDTH - getWidth() || getX() <= ArkanerdCanvas::FRAME_WIDTH) {
    reverseX();
  }
  if (getY() < ArkanerdCanvas::FRAME_TOP) {
    reverseY();
  }
  if (!sticky) {
    move(x_dir, y_dir); //sy += y_dir;
  }
}

} // namespace arkanerd
