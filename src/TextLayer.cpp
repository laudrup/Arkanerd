#include "TextLayer.h"

#include "j2me/Image.h"

#include <algorithm>

namespace arkanerd {
TextLayer::TextLayer(const std::string& text, int max_width)
  : TiledLayer(static_cast<int>(std::min(text.length(), static_cast<size_t>(max_width))), (static_cast<int>(text.length()) / max_width) + 1,
               j2me::Image::createImage("/images/font.png"), 16, 16) {
		int row = 0;
		for (int i = 0; i < static_cast<int>(text.length()); i++) {
			setCell(i - (max_width * row), row, static_cast<int>(chars_.find(text.substr(i, 1))) + 1);
			if (((i + 1) % max_width) == 0) {
				row++;
			}
		}
	}
}
