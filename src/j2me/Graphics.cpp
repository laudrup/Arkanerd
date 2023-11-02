#include "Graphics.h"
#include "SFML/System/Vector2.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

namespace {
sf::Vector2f round(const sf::Vector2f& vector) {
  return sf::Vector2f{std::round(vector.x), std::round(vector.y)};
}
} // namespace

namespace j2me {
Graphics::Graphics(sf::RenderTarget* target)
  : target_(target)
  , font_(Font::getDefaultFont()) {
}

void Graphics::setColor(int RGB) {
  const sf::Uint8 red = (RGB >> 16) & 0xff;
  const sf::Uint8 green = (RGB >>  8) & 0xff;
  const sf::Uint8 blue = RGB & 0xff;
  color_ = sf::Color{red, green, blue};
}

void Graphics::setFont(const Font& font) {
  font_ = font;
}

void Graphics::drawImage(const Image& img, int x, int y, [[maybe_unused]] int anchor) {
  auto sprite = img.sprite();
  sprite->setPosition(static_cast<float>(x), static_cast<float>(y));
  target_->draw(*sprite);
  drawables_.push_back(std::move(sprite));
}

sf::FloatRect Graphics::drawString(const std::string& str, int x, int y, int anchor) {
  auto text = std::make_unique<sf::Text>(str, font_.font_, font_.size());
  text->setStyle(font_.style());
  text->setFillColor(color_);

  if (anchor & VCENTER) {
    auto center = text->getGlobalBounds().getSize() / 2.f;
    auto localBounds = center + text->getLocalBounds().getPosition();
    auto rounded = round(localBounds);
    text->setOrigin(rounded);
    text->setPosition(target_->getView().getSize().x / 2 + x, static_cast<float>(y));
  } else {
    text->setPosition(static_cast<float>(x), static_cast<float>(y));
  }
  target_->draw(*text);
  const auto bounds = text->getLocalBounds();
  drawables_.push_back(std::move(text));
  return bounds;
}

} // namespace j2me
