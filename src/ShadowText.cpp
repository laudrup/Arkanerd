#include "ShadowText.h"

namespace arkanerd {

ShadowText::ShadowText(const std::string& str, sf::Font* font, int size)
  : text_(str, *font, size) {
}

void ShadowText::draw(sf::RenderTarget& target, sf::RenderStates) const {
  auto text = text_;
  text.setFillColor(sf::Color::Black);
  target.draw(text);
  text.setFillColor(sf::Color{0xdd, 0x22, 0x22});
  text.move(1, 1);
  target.draw(text);
}

void ShadowText::center(const sf::RenderTarget* target) {
  const sf::FloatRect rect = text_.getLocalBounds();
  text_.setOrigin(rect.left + rect.width / 2.0f, 0.f);
  text_.setPosition(target->getView().getCenter().x, 0);
}

void ShadowText::wrap(int width) {
  size_t last_space = 0;
  int line_width = 0;
  auto str = text_.getString();
  for (size_t i = 0; i < str.getSize(); ++i) {
    if (str[i] == '\n') {
      line_width = 0;
      continue;
    }
    line_width += static_cast<int>(text_.getFont()->getGlyph(str[i], text_.getCharacterSize(), false).advance);
    if (str[i] == ' ') {
      last_space = i;
    }
    if (line_width > width) {
      str[last_space] = '\n';
      line_width = 0; // TODO: Recalculate actual width
    }
  }
  text_.setString(str);
}

void ShadowText::setStyle(sf::Text::Style style) {
  text_.setStyle(style);
}

sf::FloatRect ShadowText::bounds() const {
  return text_.getLocalBounds();
}

void ShadowText::move(float x, float y) {
  text_.move(x, y);
}

} // namespace arkanerd
