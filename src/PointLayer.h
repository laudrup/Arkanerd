#pragma once

#include "ResourceManager.h"

#include "j2me/TiledLayer.h"

#include <string>

namespace arkanerd {

class PointLayer : public j2me::TiledLayer {
public:
  PointLayer(ResourceManager& resources, int digits);
  void setNum(int num);

private:
  int number_ = 0;
  int digits_ = 0;
  std::string text_;
  const std::string chars_ = "abcdefghijklmnopqrstuvwxyz 0123456789!;:'-_?";
};

} // namespace arkanerd
