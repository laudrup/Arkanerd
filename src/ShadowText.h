#pragma once

#include <SFML/Graphics.hpp>

namespace arkanerd {

class ShadowText : public sf::Drawable {
public:
  ShadowText(const std::string& str, sf::Font* font, int size);
  void draw(sf::RenderTarget& target, sf::RenderStates) const override;
  void center(const sf::RenderTarget* target);
  void wrap(int width);
  void setStyle(sf::Text::Style style);
  sf::FloatRect bounds() const;
  void move(float x, float y);

private:
  sf::Text text_;
};

} // namespace arkanerd
