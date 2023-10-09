#pragma once

#include "Command.h"
#include "SFML/Window/Keyboard.hpp"

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
  void addCommand(const Command& cmd);
  void setCommandListener(CommandListener* l);

protected:
  friend class Display;
  Displayable(MIDlet* midlet);
  virtual void handleKey(sf::Keyboard::Key key);
  virtual void handlePaint(Graphics* target);

  sf::View view_;

private:
  friend MIDlet;
  friend class List;

  MIDlet* midlet_;
  int width_ = 0;
  int height_ = 0;
  std::map<int, Command> commands_;
  CommandListener* command_listener_ = nullptr;
};

} // namespace j2me
