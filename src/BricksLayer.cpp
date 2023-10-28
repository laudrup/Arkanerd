#include "BricksLayer.h"
#include "ArkanerdCanvas.h"

namespace arkanerd {
BricksLayer::BricksLayer(ArkanerdCanvas *canvas, Level *level)
  : level_(level)
  , width_(canvas->getWidth()) {
  loadBricks();
  bricks_left_ = static_cast<int>(bricks_.size());
}

void BricksLayer::loadBricks() {
  // Place the bricks on the canvas as defined in level
  num_bricks_ = level_->getNumBricks();
  bricks_ = level_->getBricks();
  int x_pos = (width_ - 20 * level_->getBricks_x()) / 2;
  int y_pos = ArkanerdCanvas::FRAME_TOP + ArkanerdCanvas::FRAME_WIDTH;
  int count = 0;
  // Place the bricks according to the level definition
  auto it = bricks_.begin();
  for (int y = 0; y < level_->getBricks_y(); y++) {
    for (int x = 0; x < level_->getBricks_x(); x++) {
      if (!level_->isEmpty(count)) {
        it->setPosition(x_pos,y_pos);
        if (it + 1 != bricks_.end()) {
          ++it;
        }
      }
      x_pos += it->getWidth();
      count++;
    }
    x_pos = (width_ - 20 * level_->getBricks_x()) / 2;
    y_pos += it->getHeight();
  }
  bricks_left_ = num_bricks_;
}

int BricksLayer::getBricksLeft() {
  return static_cast<int>(bricks_.size()); //left_;
}

int BricksLayer::getNumBricks() {
  return num_bricks_;
}

Brick BricksLayer::getBrick() {
  return brick_;
}

bool BricksLayer::checkCollisions(j2me::Sprite* sprite) {
  for (auto it = bricks_.begin(); it != bricks_.end(); ++it) {
    if (it->collidesWith(sprite, false)) {
      brick_ = std::move(*it);
      bricks_.erase(it);
      return true;
    }
  }
  return false;
}

void BricksLayer::paint(j2me::Graphics* g) {
  for (auto& brick : bricks_) {
    brick.paint(g);
  }
}

void BricksLayer::clear() {
}

} // namespace arkanerd
