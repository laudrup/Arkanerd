#include "TitleCanvas.h"
#include "Main.h"

namespace arkanerd {

TitleCanvas::TitleCanvas(Main* main)
  : j2me::Canvas(main)
  , main_(main) {
  f_ = j2me::Font::getFont(j2me::Font::FACE_SYSTEM, j2me::Font::STYLE_PLAIN, j2me::Font::SIZE_SMALL);

  text_ = std::make_unique<TextLayer>("arkanerd", 8);
  auto bg_image = j2me::Image::createImage("/images/titlebg.png");

  text_->setPosition((getWidth() - text_->getWidth()) / 2, (getHeight() - text_->getHeight()) / 2);
  int rows = (getHeight() / bg_image.getHeight()) + 1;
  bg_layer_ = std::make_unique<j2me::TiledLayer>(1, rows, bg_image, bg_image.getWidth(), bg_image.getHeight());
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
  main_->showMenu();
}

} // namespace arkanerd
