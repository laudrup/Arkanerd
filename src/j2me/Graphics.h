#pragma once

#include "Font.h"
#include "Image.h"

#include <string>
#include <memory>
#include <vector>

namespace j2me {
class Graphics {
public:
  Graphics(sf::RenderTarget* target);
  void drawImage(const Image& img, int x, int y, int anchor);
  //void setColor(int RGB);
  //void setFont(const Font& font);
  //sf::FloatRect drawString(const Font& font, const std::string& str, int x, int y, int anchor);
  sf::RenderTarget* target() const;

  inline static constexpr int HCENTER = 1;
  inline static constexpr int VCENTER = 2;
  inline static constexpr int LEFT = 4;
  inline static constexpr int RIGHT = 8;
  inline static constexpr int TOP = 16;
  inline static constexpr int BOTTOM = 32;
  inline static constexpr int BASELINE = 64;
  inline static constexpr int SOLID = 0;
  inline static constexpr int DOTTED = 1;

private:
  sf::RenderTarget* target_;
  friend class TiledLayer;
  friend class Form;
  Font font_;
  sf::Color color_;

  std::vector<std::unique_ptr<sf::Drawable>> drawables_;
};
} // namespace j2me
