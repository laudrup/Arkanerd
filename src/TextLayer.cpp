#include "TextLayer.h"

#include <algorithm>

namespace arkanerd {
TextLayer::TextLayer(ResourceManager& resources, const std::string& text, int max_width)
  : TiledLayer(resources.getTexture("/images/font.png"),
               static_cast<int>(std::min(text.length(), static_cast<size_t>(max_width))),
               (static_cast<int>(text.length()) / max_width) + 1,
               16,
               16) {
  int row = 0;
  for (int i = 0; i < static_cast<int>(text.length()); i++) {
    setCell(i - (max_width * row), row, static_cast<int>(chars_.find(text.substr(i, 1))) + 1);
    if (((i + 1) % max_width) == 0) {
      row++;
    }
  }
}

} // namespace arkanerd

