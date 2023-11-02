#include "TextCanvas.h"

#include "j2me/Image.h"
#include "j2me/MIDlet.h"

#include <SFML/Window/Keyboard.hpp>

#include <cstdlib>

#include <iostream>

namespace {
std::string wrap_text(std::string str, const j2me::Font& font, int width) {
  size_t last_space = 0;
  int line_width = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == '\n') {
      line_width = 0;
      continue;
    }
    line_width += font.getWidth(str[i]);
    if (str[i] == ' ') {
      last_space = i;
    }
    if (line_width > width) {
      str[last_space] = '\n';
      line_width = 0; // TODO: Recalculate actual width
    }
  }
  return str;
}
} // namespace

namespace arkanerd {

TextCanvas::TextCanvas(j2me::MIDlet* midlet, const std::string& title, const items_type& items, std::function<void()> on_dismiss)
  : BackgroundCanvas(midlet)
  , on_dismiss_(on_dismiss)
  , title_(title)
  , items_(items) {
}

void TextCanvas::paint(j2me::Graphics *g) {
  BackgroundCanvas::paint(g);

  height_ = 5;
  g->setFont(j2me::Font::getFont(j2me::Font::FACE_SYSTEM, j2me::Font::STYLE_PLAIN, j2me::Font::SIZE_MEDIUM));;
  g->setColor(0x00000000);
  g->drawString(title_, 0, height_ + offset_, j2me::Graphics::TOP | j2me::Graphics::VCENTER);
  g->setColor(0x00DD2222);
  height_ += static_cast<int>(g->drawString(title_, 1, height_ + offset_ + 1, j2me::Graphics::TOP | j2me::Graphics::VCENTER).height);
  height_ += 5;
  auto font = j2me::Font::getDefaultFont();
  g->setFont(font);
  for (const auto& item : items_) {
    if (std::holds_alternative<std::string>(item)) {
      const auto text = wrap_text(std::get<std::string>(item), font, getWidth() - 20);
      g->setColor(0x00000000);
      g->drawString(text, 10, height_ + offset_, j2me::Graphics::TOP | j2me::Graphics::HCENTER);
      g->setColor(0x00DD2222);
      height_ += static_cast<int>(g->drawString(text, 11, height_ + offset_ + 1, j2me::Graphics::TOP | j2me::Graphics::HCENTER).height);
      height_ += 10;
    } else {
      const auto image = std::get<ImageItem>(item).image;
      g->drawImage(image, 15, height_ + offset_, 0);
      g->setColor(0x00000000);
      g->drawString(std::get<ImageItem>(item).text, image.getWidth() + 20, height_ + offset_ - 2, 0);
      g->setColor(0x00DD2222);
      g->drawString(std::get<ImageItem>(item).text, image.getWidth() + 20, height_ + offset_ - 1, 0);
      height_ += image.getHeight() + 5;
    }
  }
}

void TextCanvas::keyPressed(sf::Keyboard::Key key) {
  switch (key) {
    case sf::Keyboard::Key::Up:
      if (offset_ < 10) {
        offset_ += 10;
      }
      break;
    case sf::Keyboard::Key::Down:
      if (std::abs(offset_) < height_ - getHeight()) {
        offset_ -= 10;
      }
      break;
    default:
      on_dismiss_();
  }
}

} // namespace arkanerd
