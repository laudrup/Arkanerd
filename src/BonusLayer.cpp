#include "BonusLayer.h"
#include "ArkanerdCanvas.h"
#include "Main.h"

namespace arkanerd {

BonusLayer::BonusLayer(ArkanerdCanvas* canvas)
  : canvas_(canvas) {
}

void BonusLayer::addBonus(int x, int y, int type) {
  BonusBrick bonus(canvas_->main_->resources, type);
  bonus.setPosition(x, y);
  bonus_bricks_.push_back(std::move(bonus));
}

void BonusLayer::clear() {
}

void BonusLayer::reset() {
  bonus_bricks_.clear();
}

void BonusLayer::update() {
  for (auto it = bonus_bricks_.begin(); it != bonus_bricks_.end();) {
    it->setPosition(it->getX(), it->getY() + 1);
    it->nextFrame();
    if (it->getY() > canvas_->getHeight()) {
      it = bonus_bricks_.erase(it);
    } else {
      ++it;
    }
  }
}

int BonusLayer::getType() {
  return type_;
}

bool BonusLayer::checkCollisions(j2me::Sprite *sprite) {
  for (auto it = bonus_bricks_.begin(); it != bonus_bricks_.end(); ++it) {
    if (it->collidesWith(sprite, false)) {
      type_ = it->getType();
      bonus_bricks_.erase(it);
      return true;
    }
  }
  return false;
}

void BonusLayer::paint(j2me::Graphics *g) {
  for (auto& bonus : bonus_bricks_) {
    bonus.paint(g);
  }
}

} // namespace arkanerd
