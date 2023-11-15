#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <map>

namespace j2me {

class CommandListener;
class Command;
class MIDlet;
class Graphics;

class Displayable {
public:
  virtual ~Displayable() = default;
  int getWidth() const;
  int getHeight() const;
  void setCommandListener(CommandListener* l);

protected:
  friend class Display;
  Displayable(MIDlet* midlet);
  virtual void handleKey(sf::Keyboard::Key key);
  virtual void handlePaint(Graphics* target);

  sf::View view_;
  MIDlet* midlet_;

private:
  friend MIDlet;
  friend class List;

  int width_ = 0;
  int height_ = 0;
  CommandListener* command_listener_ = nullptr;
};

} // namespace j2me
