#include "TitleCanvas.h"
#include "Main.h"

#include "j2me/Manager.h"

#include <fstream>

namespace arkanerd {

TitleCanvas::TitleCanvas(Main* main)
  : j2me::Canvas(main)
  , main_(main) {
  setFullScreenMode(true);
  width_ = getWidth();
  height_ = getHeight();
  f_ = j2me::Font::getFont(j2me::Font::FACE_SYSTEM, j2me::Font::STYLE_PLAIN, j2me::Font::SIZE_SMALL);

  text_ = new TextLayer("arkanerd", 8);
  bg_image_ = j2me::Image::createImage("/images/titlebg.png");

  text_->setPosition((width_ - text_->getWidth()) / 2, (height_ - text_->getHeight()) / 2);
  int rows = (height_ / bg_image_.getHeight()) + 1;
  bg_layer_ = new j2me::TiledLayer(1, rows, bg_image_, bg_image_.getWidth(), bg_image_.getHeight());
  bg_layer_->fillCells(0,0,1,rows,1);

  std::ifstream ins{"/music/intro.mid"};
  player_ = j2me::Manager::createPlayer(ins, "audio/midi");
  player_.addPlayerListener(this);
  player_.start();
}

void TitleCanvas::paint(j2me::Graphics *g) {
  bg_layer_->paint(g);
  text_->paint(g);
  g->setColor(0x00000000);
  g->drawString(S1_, width_ / 2, height_ / 2 + height_ / 4, j2me::Graphics::TOP | j2me::Graphics::HCENTER);
  g->drawString(S2_, width_ / 2, height_ / 2 + height_ / 4 + f_.getHeight(), j2me::Graphics::TOP | j2me::Graphics::HCENTER);
  g->setColor(0x00DD2222);
  g->drawString(S1_, width_ / 2, (height_ / 2 + height_ / 4) + 2, j2me::Graphics::TOP | j2me::Graphics::HCENTER);
  g->drawString(S2_, width_ / 2, (height_ / 2 + height_ / 4 + f_.getHeight()) + 2, j2me::Graphics::TOP | j2me::Graphics::HCENTER);
}

void TitleCanvas::playerUpdate(const j2me::Player* /*player*/, const std::string& event, const char* /*data*/) {
  if (event == END_OF_MEDIA) {
    player_.stop();
    player_.close();
    main_->showMenu();
	}
}

void TitleCanvas::keyPressed(int /*key*/) {
  player_.stop();
  player_.close();
  main_->showMenu();
}

} // namespace arkanerd
