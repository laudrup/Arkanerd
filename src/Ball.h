#pragma once

#include "ResourceManager.h"
#include "j2me/Sprite.h"

namespace arkanerd {

class ArkanerdCanvas;

class Ball : public j2me::Sprite {
public:
  Ball(ResourceManager& resources, ArkanerdCanvas *canvas);

  //TODO: Set ball to start position
  void setSticky(bool b);
  bool isSticky();
  void setAngle(int x_angle, int y_angle);
  void reverseX();
  void reverseY();
  void update();

private:
  ArkanerdCanvas* canvas_;
  int x_dir = 0;
  int y_dir = 0;
  int width = 0;
  bool sticky = false;
};

} // namespace arkanerd
