#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

namespace j2me {
class Graphics;

class Image {
public:
  Image() = default;
  static Image createImage(const sf::Texture* texture);
  static Image createImage(const Image& image, int x, int y, int width, int height, int transform);

  int getWidth() const;
  int getHeight() const;

private:
  friend class Graphics;
  explicit Image(const sf::Texture* texture);
  Image(const sf::Image&, const sf::IntRect& area);
  std::unique_ptr<sf::Sprite> sprite() const;

  sf::Texture texture_;
};
} // namespace j2me
