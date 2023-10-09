#include "GameCanvas.h"

#include <cstdlib>
#include <iostream>

namespace j2me {

int GameCanvas::getKeyStates() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    return LEFT_PRESSED;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    return RIGHT_PRESSED;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    return FIRE_PRESSED;
  }
  return 0;
}

void GameCanvas::flushGraphics() {
  //abort();
}

void GameCanvas::paint(Graphics* g) {
  graphics_ = g;
}

Graphics* GameCanvas::getGraphics() {
  return graphics_;
}

void GameCanvas::keyPressed(int /*keyCode*/) {
}

} // namespace j2me
