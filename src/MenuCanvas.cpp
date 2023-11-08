#include "MenuCanvas.h"

#include "j2me/MIDlet.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace arkanerd {

MenuCanvas::MenuCanvas(j2me::MIDlet* midlet, const std::string& title, const std::vector<Entry>& entries, std::function<void()> on_dismiss)
  : BackgroundCanvas(midlet)
  , on_dismiss_(on_dismiss)
  , font_(midlet_->resources.getFont("fonts/Skranji-Regular.ttf"))
  , title_(title, font_, 16)
  , entries_(entries)
  , selected_(entries_.begin()) {
}

void MenuCanvas::paint(j2me::Graphics *g) {
  BackgroundCanvas::paint(g);

  float y_pos = 0;
  title_.center(g->target());
  title_.move(0, y_pos);
  g->target()->draw(title_);
  y_pos += title_.bounds().height + 10.f;

  for (auto entry = entries_.begin(); entry != entries_.end(); ++entry) {
    ShadowText text{entry->name, font_, 12};
    if (entry == selected_) {
      text.setStyle(sf::Text::Bold);
    }

    text.center(g->target());
    text.move(0, y_pos);
    g->target()->draw(text);
    y_pos += text.bounds().height + 10.f;
  }
}

void MenuCanvas::keyPressed(sf::Keyboard::Key key) {
  switch (key) {
    case sf::Keyboard::Key::Up:
      if (selected_ != entries_.begin()) {
        selected_--;
      }
      break;
    case sf::Keyboard::Key::Down:
      if (selected_ + 1 != entries_.end()) {
        selected_++;
      }
      break;
    case sf::Keyboard::Key::Escape:
      on_dismiss_();
      return;
    case sf::Keyboard::Space:
    case sf::Keyboard::Return: {
      selected_->on_selected();
      return;
    }
    default:
      break;
  }
}

} // namespace arkanerd
