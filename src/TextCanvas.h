#pragma once

#include "BackgroundCanvas.h"
#include "ShadowText.h"

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
  sf::Font* font_;
  ShadowText title_;
  items_type items_;
  float y_pos_ = 0;
  float offset_ = 0;
};

} // namespace arkanerd
