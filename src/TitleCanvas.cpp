#include "TitleCanvas.h"
#include "ShadowText.h"

#include <j2me/MIDlet.h>

namespace arkanerd {

TitleCanvas::TitleCanvas(j2me::MIDlet* midlet, std::function<void()> on_dismiss)
  : BackgroundCanvas(midlet)
  , on_dismiss_(on_dismiss)
  , font_(midlet_->resources.getFont("fonts/Skranji-Regular.ttf")) {
  text_ = std::make_unique<TextLayer>(midlet_->resources, "arkanerd", 8);
  text_->setPosition((getWidth() - text_->getWidth()) / 2, (getHeight() - text_->getHeight()) / 2);
}

void TitleCanvas::paint(j2me::Graphics *g) {
  BackgroundCanvas::paint(g);
  text_->paint(g);
  auto font = midlet_->resources.getFont("fonts/Skranji-Regular.ttf");

  ShadowText text_1{S1_, font, 10};
  text_1.move(getWidth() / 2.f, getHeight() / 2.f + getHeight() / 4.f);
  g->target()->draw(text_1);

  ShadowText text_2{S2_, font, 10};
  text_2.move(getWidth() / 2.f, getHeight() / 2.f + getHeight() / 4.f + text_1.bounds().height);
  g->target()->draw(text_2);
}

void TitleCanvas::keyPressed(sf::Keyboard::Key /*key*/) {
  on_dismiss_();
}

} // namespace arkanerd
