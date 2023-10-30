#include "Board.h"

#include "j2me/Image.h"

namespace arkanerd {

Board::Board(ResourceManager& resources)
  : j2me::Sprite(j2me::Image::createImage(resources.getTexture("/images/board.png"))) {
}

} // namespace arkanerd
