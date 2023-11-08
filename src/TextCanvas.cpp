#include "TextCanvas.h"

#include "j2me/Image.h"
#include "j2me/MIDlet.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <cstdlib>

namespace arkanerd {

TextCanvas::TextCanvas(j2me::MIDlet* midlet, const std::string& title, const items_type& items, std::function<void()> on_dismiss)
  : BackgroundCanvas(midlet)
  , on_dismiss_(on_dismiss)
  , font_(midlet_->resources.getFont("fonts/Skranji-Regular.ttf"))
  , title_(title, font_, 16)
  , items_(items) {
}

void TextCanvas::paint(j2me::Graphics *g) {
  BackgroundCanvas::paint(g);

  y_pos_ = 0;
  title_.center(g->target());
  title_.move(0, y_pos_ + offset_);
  g->target()->draw(title_);
  y_pos_ += title_.bounds().height + 10;

  for (const auto& item : items_) {
    if (std::holds_alternative<std::string>(item)) {
      ShadowText text{std::get<std::string>(item), font_, 8};
      text.wrap(getWidth() - 20);
      text.move(10, y_pos_ + offset_);
      g->target()->draw(text);
      y_pos_ += text.bounds().height + 10;
    } else {
      const auto& image = std::get<ImageItem>(item).image;
      g->drawImage(image, 15, static_cast<int>(y_pos_ + offset_), 0);

      ShadowText text{std::get<ImageItem>(item).text, font_, 8};
      text.move(static_cast<float>(image.getWidth() + 20), y_pos_ + offset_ - 2);
      g->target()->draw(text);
      y_pos_ += image.getHeight() + 5;
    }
  }
}

void TextCanvas::keyPressed(sf::Keyboard::Key key) {
  switch (key) {
    case sf::Keyboard::Key::Up:
      if (offset_ < 0) {
        offset_ += 10;
      }
      break;
    case sf::Keyboard::Key::Down:
      if (std::abs(offset_) < y_pos_ - getHeight()) {
        offset_ -= 10;
      }
      break;
    default:
      on_dismiss_();
  }
}

} // namespace arkanerd
