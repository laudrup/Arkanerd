#pragma once

#include "BonusBrick.h"

#include "j2me/LayerManager.h"
#include "j2me/Sprite.h"

#include <vector>

namespace arkanerd {

class ArkanerdCanvas;

class Bonus {

public:
  Bonus(j2me::LayerManager *layerManager, ArkanerdCanvas *canvas);
  void addBonus(int x, int y, int type);
  void clear();
  void update();
  // Return the type of the last bonus hit
  int getType();
  bool checkCollisions(j2me::Sprite *sprite);

private:
  BonusBrick* bonus_brick_ = nullptr;
  std::vector<BonusBrick*> bonus_bricks_;
  j2me::LayerManager* layer_manager_;
  ArkanerdCanvas* canvas_;
};

} // namespace arkanerd
