#pragma once

#include <SFML/Graphics.hpp>

namespace j2me {

class Displayable;
class MIDlet;

class Display {
public:
  Display();
  static Display* getDisplay(j2me::MIDlet* m);
  void setCurrent(Displayable* nextDisplayable);
  Displayable* getCurrent() const;

private:
  friend MIDlet;
  sf::RenderWindow window_;
  Displayable* displayable_ = nullptr;
};

} // namespace j2me
