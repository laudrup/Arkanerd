#include "Displayable.h"
#include "Canvas.h"
#include <iostream>

namespace j2me {

Displayable::Displayable(MIDlet *midlet)
  : view_(sf::FloatRect(0, 0, 240, 200))
  , midlet_(midlet) {
}

int Displayable::getWidth() const {
  return static_cast<int>(view_.getSize().x);
}

int Displayable::getHeight() const {
  return static_cast<int>(view_.getSize().y);
}

void Displayable::handleKey(sf::Keyboard::Key key) {
  auto canvas = dynamic_cast<Canvas*>(this);
  if (canvas) {
    canvas->keyPressed(key);
    return;
  }
}

void Displayable::handlePaint(Graphics* g) {
  auto canvas = dynamic_cast<Canvas*>(this);
  if (canvas) {
    canvas->paint(g);
  }
}

} // namespace j2me
