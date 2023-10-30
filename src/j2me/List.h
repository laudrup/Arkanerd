#pragma once

#include "Displayable.h"
#include "Choice.h"
#include "Command.h"

#include <SFML/Window/Keyboard.hpp>

#include <string>
#include <vector>

namespace j2me {
class Image;

class List : public Displayable, public Choice {
public:
  List(MIDlet* midlet, const std::string& title, int listType);
  List(MIDlet* midlet, const std::string& title, int listType, const std::vector<std::string>& stringElements, const std::vector<Image>& imageElements);
  int append(const std::string& stringPart, const j2me::Image& imagePart);
  int size() const;
  int getSelectedFlags(std::vector<bool>& selectedArray_return) const;
  int getSelectedIndex() const;
  void setSelectedIndex(int elementNum, bool selected);

  inline static const Command SELECT_COMMAND{"", Command::SCREEN, 0};

private:
  void handleKey(sf::Keyboard::Key key) override;
  void handlePaint(Graphics* target) override;

  std::string title_;
  int list_type_;
  std::vector<std::string> items_;
  size_t selected_ = 0;
};

} // namespace j2me
