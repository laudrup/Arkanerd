#include "Display.h"
#include "Displayable.h"
#include "MIDlet.h"

#include <cstdlib>

namespace {
sf::VideoMode get_video_mode() {
  return {sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2};
}
} // namespace

namespace j2me {

Display::Display()
  : window_{get_video_mode(), "Arkanerd"} {
  window_.setFramerateLimit(20);
}

Display* Display::getDisplay(j2me::MIDlet* m) {
  return &m->display_;
}

void Display::setCurrent(Displayable* nextDisplayable) {
  displayable_ = nextDisplayable;
  window_.setView(displayable_->view_);
}

Displayable* Display::getCurrent() const {
  return displayable_;
}

} // namespace j2me
