#pragma once

#include "BackgroundCanvas.h"

#include "j2me/Graphics.h"
#include "j2me/Image.h"

#include <functional>
#include <string>
#include <variant>
#include <vector>

namespace arkanerd {

class TextCanvas : public BackgroundCanvas {

public:
  struct ImageItem {
    j2me::Image image;
    std::string text;
  };
  using items_type = std::vector<std::variant<std::string, ImageItem>>;
  TextCanvas(j2me::MIDlet* midlet, const std::string& title, const items_type& items, std::function<void()> on_dismiss);
  void keyPressed(sf::Keyboard::Key key) final;

protected:
  void paint(j2me::Graphics* g) final;

private:
  std::function<void()> on_dismiss_;
  std::string title_;
  items_type items_;
  int offset_ = 10;
  int height_ = 0;
};

} // namespace arkanerd
