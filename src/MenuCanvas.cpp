#include "MenuCanvas.h"

#include "j2me/MIDlet.h"

#include <SFML/Window/Keyboard.hpp>

namespace arkanerd {

MenuCanvas::MenuCanvas(j2me::MIDlet* midlet, const std::string& title, const std::vector<Entry>& entries, std::function<void()> on_dismiss)
  : BackgroundCanvas(midlet)
  , on_dismiss_(on_dismiss)
  , title_(title)
  , entries_(entries)
  , selected_(entries_.begin()) {
}

void MenuCanvas::paint(j2me::Graphics *g) {
  BackgroundCanvas::paint(g);
  int y_pos = 15;
  g->setFont(j2me::Font::getFont(j2me::Font::FACE_SYSTEM, j2me::Font::STYLE_PLAIN, j2me::Font::SIZE_LARGE));;
  g->setColor(0x00000000);
  g->drawString(title_, 0, y_pos, j2me::Graphics::TOP | j2me::Graphics::VCENTER);
  g->setColor(0x00DD2222);
  y_pos += static_cast<int>(g->drawString(title_, 1, ++y_pos, j2me::Graphics::TOP | j2me::Graphics::VCENTER).height);

  y_pos += 10;
  const auto font = j2me::Font::getFont(j2me::Font::FACE_SYSTEM, j2me::Font::STYLE_PLAIN, j2me::Font::SIZE_MEDIUM);
  const auto selected_font = j2me::Font::getFont(j2me::Font::FACE_SYSTEM, j2me::Font::STYLE_BOLD, j2me::Font::SIZE_MEDIUM);
  for (auto entry = entries_.begin(); entry != entries_.end(); ++entry) {
    if (entry == selected_) {
      g->setFont(selected_font);
    } else {
      g->setFont(font);
    }
    g->setColor(0x00000000);
    g->drawString(entry->name, 0, y_pos, j2me::Graphics::TOP | j2me::Graphics::VCENTER);
    g->setColor(0x00DD2222);
    y_pos += static_cast<int>(g->drawString(entry->name, 1, y_pos + 1, j2me::Graphics::TOP | j2me::Graphics::VCENTER).height);
    y_pos += 10;
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
      //on_dismiss_();
  }
}

} // namespace arkanerd
