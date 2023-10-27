#include "List.h"
#include "Choice.h"
#include "CommandListener.h"
#include "Displayable.h"
#include "Graphics.h"

#include "SFML/Window/Keyboard.hpp"

#include <string>
#include <vector>

namespace j2me {
List::List(MIDlet* midlet, const std::string& title, int listType)
  : Displayable(midlet)
  , title_(title)
  , list_type_(listType) {
}

List::List(MIDlet *midlet, const std::string& title, int listType,
           const std::vector<std::string>& stringElements, const std::vector<Image>& /*imageElements*/)
  : Displayable(midlet)
  , title_(title)
  , list_type_(listType)
  , items_(stringElements) {
}

int List::append(const std::string& stringPart, const j2me::Image& /*imagePart*/) {
  items_.push_back(stringPart);
  return static_cast<int>(items_.size());
}

int List::size() const {
  return 0;
}

int List::getSelectedFlags(std::vector<bool>& /*selectedArray_return*/) const {
  return 0;
}

int List::getSelectedIndex() const {
  return static_cast<int>(selected_);
}

void List::setSelectedIndex(int elementNum, bool /*selected*/) {
  selected_ = elementNum;
}

void List::handleKey(sf::Keyboard::Key key) {
  switch (key) {
    case sf::Keyboard::Up:
      if (selected_ != 0) {
        selected_--;
      }
      break;
    case sf::Keyboard::Down:
      if (selected_ + 1 != items_.size()) {
        selected_++;
      }
      break;
    case sf::Keyboard::Space:
    case sf::Keyboard::Return: {
      if (list_type_ == Choice::MULTIPLE) {
      } else if (list_type_ == Choice::IMPLICIT) {
        auto displayable = dynamic_cast<Displayable*>(this);
        if (displayable->command_listener_ != nullptr) {
          displayable->command_listener_->commandAction(SELECT_COMMAND, *displayable);
          return;
        }
      }
      break;
    }
    default:
      break;
  }
  Displayable::handleKey(key);
}

void List::handlePaint(Graphics* g) {
  const auto font = Font::getFont(Font::FACE_SYSTEM, Font::STYLE_PLAIN, Font::SIZE_LARGE);
  const auto selected_font = Font::getFont(Font::FACE_SYSTEM, Font::STYLE_BOLD, Font::SIZE_LARGE);
  g->setFont(selected_font);
  g->drawString(title_, 0, 10, Graphics::TOP | Graphics::VCENTER);
  int y = Font::getDefaultFont().getHeight() + 30;
  for (size_t i = 0; i < items_.size(); ++i) {
    if (i == selected_) {
      g->setFont(selected_font);
    } else {
      g->setFont(font);
    }
    const auto str = items_[i];
    g->drawString(str, 0, y, Graphics::TOP | Graphics::VCENTER);
    y += Font::getDefaultFont().getHeight() + 10;
  }
}

} // namespace j2me
