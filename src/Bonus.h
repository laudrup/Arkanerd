#pragma once

/*
  Bonus.java

  Arkanerd - An Arkanoid/Breakout like game for J2ME mobile phones
  Copyright (C) 2006  Kasper Laudrup

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

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
