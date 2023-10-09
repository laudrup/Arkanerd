#pragma once

#include "Displayable.h"
#include "Item.h"

#include <memory>
#include <string>
#include <vector>

namespace j2me {

class MIDlet;
class Form : public Displayable {
public:
  Form(MIDlet* midlet, const std::string& title);
  int append(std::unique_ptr<Item> item);
  int append(const std::string& str);

private:
  void handleKey(sf::Keyboard::Key key) override;
  void handlePaint(Graphics* target) override;

  std::string title_;
  std::vector<std::unique_ptr<Item>> items_;
};

} // namespace j2me
