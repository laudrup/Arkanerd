#pragma once

#include "ResourceManager.h"

#include "j2me/TiledLayer.h"

#include <string>

namespace arkanerd {
class LivesLayer : public j2me::TiledLayer {
public:
  LivesLayer(ResourceManager& resources, int lives);
  void update(int lives);

private:
  std::string text_;
  const std::string chars_ = "abcdefghijklmnopqrstuvwxyz 0123456789!;:'-_?";
};

} // namespace arkanerd
