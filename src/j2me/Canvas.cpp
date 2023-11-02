#include "Canvas.h"

#include <cstdlib>

namespace j2me {

void Canvas::setFullScreenMode(bool) {
  //abort();
}

void Canvas::keyPressed(sf::Keyboard::Key /*keyCode*/) {
  abort();
}

} // namespace j2me
