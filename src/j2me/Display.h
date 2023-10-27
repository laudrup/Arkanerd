#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

namespace j2me {

class Displayable;
class MIDlet;

class Display {
public:
  Display();
  static Display* getDisplay(j2me::MIDlet* m);
  void setCurrent(std::unique_ptr<Displayable> nextDisplayable);
  Displayable* getCurrent() const;

private:
  friend MIDlet;
  sf::RenderWindow window_;
  std::unique_ptr<Displayable> displayable_;
};

} // namespace j2me
