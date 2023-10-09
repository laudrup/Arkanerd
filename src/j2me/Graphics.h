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

  //void clear();
  //void setClip(int x, int y, int width, int height);
  void drawImage(const Image& img, int x, int y, int anchor);
  //void drawRect(int x, int y, int width, int height);
  void setColor(int RGB);
  void setFont(const Font& font);
  //void setColor(int red, int green, int blue);
  //void fillRect(int x, int y, int width, int height);
  void drawString(const std::string& str, int x, int y, int anchor);
  //void drawLine(int x1, int y1, int x2, int y2);
  //void setFont(const Font& font);
  //void drawChars(const char* data, int offset, int length, int x, int y, int anchor);

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
  friend class TiledLayer;
  friend class Form;
  sf::RenderTarget* target_;
  Font font_;
  sf::Color color_;

  std::vector<std::unique_ptr<sf::Drawable>> drawables_;
};
} // namespace j2me
