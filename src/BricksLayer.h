#pragma once

#include "Level.h"
#include "Brick.h"
#include "ArkanerdCanvas.h"

#include "j2me/Layer.h"
#include "j2me/LayerManager.h"

#include <memory>
#include <vector>

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
