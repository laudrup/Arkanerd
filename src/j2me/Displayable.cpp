#include "Displayable.h"
#include "Canvas.h"
#include "CommandListener.h"
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

void Displayable::addCommand(const Command& cmd) {
  commands_.insert({cmd.getCommandType(), cmd});
}

void Displayable::setCommandListener(CommandListener* l) {
  command_listener_ = l;
}

void Displayable::handleKey(sf::Keyboard::Key key) {
  auto canvas = dynamic_cast<Canvas*>(this);
  if (canvas) {
    canvas->keyPressed(key);
  }
  if (command_listener_ == nullptr) {
    return;
  }
  switch (key) {
    case sf::Keyboard::Key::Escape: {
      const auto it = commands_.find(Command::BACK);
      if (it != commands_.end()) {
        command_listener_->commandAction(it->second, *this);
      }
      break;
    }
    default:
      break;
  }
}

void Displayable::handlePaint(Graphics* g) {
  auto canvas = dynamic_cast<Canvas*>(this);
  if (canvas) {
    canvas->paint(g);
  }
}

} // namespace j2me
