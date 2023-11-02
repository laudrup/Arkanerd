#include "BackgroundCanvas.h"

#include "j2me/MIDlet.h"

namespace arkanerd {

BackgroundCanvas::BackgroundCanvas(j2me::MIDlet* midlet)
  : j2me::Canvas(midlet) {
  const auto texture = midlet_->resources.getTexture("/images/titlebg.png");
  int rows = (getHeight() / texture->getSize().y) + 1;
  bg_layer_ = std::make_unique<j2me::TiledLayer>(texture, 1, rows, texture->getSize().x, texture->getSize().y);
  bg_layer_->fillCells(0, 0, 1, rows, 1);
}

void BackgroundCanvas::paint(j2me::Graphics *g) {
  bg_layer_->paint(g);
}

} // namespace arkanerd
