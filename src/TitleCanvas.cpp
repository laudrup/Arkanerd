#include "TitleCanvas.h"

#include <j2me/MIDlet.h>

namespace arkanerd {

TitleCanvas::TitleCanvas(j2me::MIDlet* midlet, std::function<void()> on_dismiss)
  : j2me::Canvas(midlet)
  , on_dismiss_(on_dismiss) {
  f_ = j2me::Font::getFont(j2me::Font::FACE_SYSTEM, j2me::Font::STYLE_PLAIN, j2me::Font::SIZE_SMALL);

  text_ = std::make_unique<TextLayer>(midlet_->resources, "arkanerd", 8);
  text_->setPosition((getWidth() - text_->getWidth()) / 2, (getHeight() - text_->getHeight()) / 2);

  const auto texture = midlet_->resources.getTexture("/images/titlebg.png");
  int rows = (getHeight() / texture->getSize().y) + 1;
  bg_layer_ = std::make_unique<j2me::TiledLayer>(texture, 1, rows, texture->getSize().x, texture->getSize().y);
  bg_layer_->fillCells(0, 0, 1, rows, 1);
}

void TitleCanvas::paint(j2me::Graphics *g) {
  bg_layer_->paint(g);
  text_->paint(g);
  g->setColor(0x00000000);
  g->drawString(S1_, getWidth() / 2, getHeight() / 2 + getHeight() / 4, j2me::Graphics::TOP | j2me::Graphics::HCENTER);
  g->drawString(S2_, getWidth() / 2, getHeight() / 2 + getHeight() / 4 + f_.getHeight(), j2me::Graphics::TOP | j2me::Graphics::HCENTER);
  g->setColor(0x00DD2222);
  g->drawString(S1_, getWidth() / 2, (getHeight() / 2 + getHeight() / 4) + 2, j2me::Graphics::TOP | j2me::Graphics::HCENTER);
  g->drawString(S2_, getWidth() / 2, (getHeight() / 2 + getHeight() / 4 + f_.getHeight()) + 2, j2me::Graphics::TOP | j2me::Graphics::HCENTER);
}

void TitleCanvas::keyPressed(int /*key*/) {
  on_dismiss_();
}

} // namespace arkanerd
