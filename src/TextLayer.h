#pragma once

#include "ResourceManager.h"

#include "j2me/TiledLayer.h"

#include <string>

namespace arkanerd {

class TextLayer : public j2me::TiledLayer {
public:
  TextLayer(ResourceManager& resources, const std::string& text, int max_width);

  static constexpr int WIDTH = 16;
  static constexpr int HEIGHT = 16;

private:
  const std::string chars_ = "abcdefghijklmnopqrstuvwxyz 0123456789!;:'-_?";
};

} // namespace arkanerd
