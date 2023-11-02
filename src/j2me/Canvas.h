#pragma once

#include "Displayable.h"

namespace j2me {

class Canvas : public Displayable {
public:
  virtual ~Canvas() = default;
  virtual void keyPressed(sf::Keyboard::Key keyCode);

protected:
  friend class MIDlet;
  friend class Displayable;
  using Displayable::Displayable;

  void setFullScreenMode(bool);
  virtual void paint(Graphics* g) = 0;
};

} // namespace j2me
