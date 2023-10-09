#include "Bonus.h"
#include "ArkanerdCanvas.h"

#include <algorithm>
#include <iostream>

namespace arkanerd {

Bonus::Bonus(j2me::LayerManager* layer_manager, ArkanerdCanvas* canvas)
  : layer_manager_(layer_manager)
  , canvas_(canvas) {
}

void Bonus::addBonus(int x, int y, int type) {
  bonus_brick_ = new BonusBrick(type);
  bonus_brick_->setPosition(x, y);
  layer_manager_->append(bonus_brick_);
  bonus_bricks_.push_back(bonus_brick_);
}

void Bonus::clear() {
  for (auto brick : bonus_bricks_) {
    layer_manager_->remove(brick);
  }
  bonus_bricks_.clear();
}

void Bonus::update() {
  for (auto it = bonus_bricks_.begin(); it != bonus_bricks_.end();) {
    (*it)->setPosition(bonus_brick_->getX(), bonus_brick_->getY() + 1);
    (*it)->nextFrame();
    if ((*it)->getY() > canvas_->getHeight()) {
      it = bonus_bricks_.erase(it);
    } else {
      ++it;
    }
  }
}

int Bonus::getType() {
  return bonus_brick_->getType();
}

bool Bonus::checkCollisions(j2me::Sprite *sprite) {
  for (auto it = bonus_bricks_.begin(); it != bonus_bricks_.end(); ++it) {
    if ((*it)->collidesWith(sprite, false)) {
      layer_manager_->remove(*it);
      bonus_bricks_.erase(it);
      return true;
    }
  }
  return false;
}

} // namespace arkanerd
