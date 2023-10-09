#pragma once

#include "Level.h"
#include "Brick.h"
#include "ArkanerdCanvas.h"

#include "j2me/Layer.h"
#include "j2me/LayerManager.h"

#include <memory>
#include <vector>

/*
  Bricks.java

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

namespace arkanerd {
class BricksLayer : public j2me::Layer {
public:
  BricksLayer(ArkanerdCanvas *canvas, Level *level);
  int getBricksLeft();
  int getNumBricks();
  //Brick* getBrick(int i);

  // Get the last hit brick
  Brick getBrick();
  bool checkCollisions(j2me::Sprite *sprite);
  void paint(j2me::Graphics* g) final;
  void clear() override;

private:
  void loadBricks();
  //j2me::LayerManager* layer_manager_ = nullptr;

  std::vector<Brick> bricks_;
  Level* level_ = nullptr;
  Brick brick_;
  int width_ = 0;
  int num_bricks_ = 0;
  int bricks_left_ = 0;
};

} // namespace arkanerd
