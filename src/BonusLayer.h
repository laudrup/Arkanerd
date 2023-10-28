#pragma once

#include "BonusBrick.h"

#include "j2me/Sprite.h"

#include <vector>

namespace arkanerd {

class ArkanerdCanvas;

class BonusLayer : public j2me::Layer {

public:
  BonusLayer(ArkanerdCanvas* canvas);
  void addBonus(int x, int y, int type);
  void update();
  // Return the type of the last bonus hit
  int getType();
  bool checkCollisions(j2me::Sprite* sprite);
  void paint(j2me::Graphics* g) final;
  void clear() final;
  void reset();

private:
  int type_ = 0;
  std::vector<BonusBrick> bonus_bricks_;
  ArkanerdCanvas* canvas_;
};

} // namespace arkanerd
