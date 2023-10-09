#include "LivesLayer.h"

#include "j2me/Image.h"

namespace arkanerd {
	LivesLayer::LivesLayer(int lives)
    : TiledLayer(5, 1, j2me::Image::createImage("/images/font.png"), 16, 16) {
		update(lives);
	}

	void LivesLayer::update(int lives) {
		// Clear the collumns
		fillCells(0,0,5,1,0);
		// Fill in the hearts
		for (int i = 2; i < lives + 2 && i < getColumns(); i++) {
			setCell(i,0,47);
		}
		if (lives > 3) {
			// Fill in the number of lives
			text_ = std::to_string(lives);
			if (lives > 9) {
				setCell(0,0, static_cast<int>(chars_.find(text_.substr(0, 1))) + 1);
				setCell(1,0, static_cast<int>(chars_.find(text_.substr(1, 1))) + 1);
			} else {
				setCell(1,0, static_cast<int>(chars_.find(text_.substr(0, 1))) + 1);
			}
		}
	}
}
