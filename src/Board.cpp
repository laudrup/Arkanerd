#include "Board.h"

#include "j2me/Image.h"

namespace arkanerd {
std::string Board::BOARD_FILE = "/images/board.png";

	Board::Board()
    : j2me::Sprite(j2me::Image::createImage(BOARD_FILE)) {
	}
} // namespace arkanerd
