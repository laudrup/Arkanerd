#include "Font.h"

#include <cstdlib>
#include <memory>

namespace {
sf::Text::Style to_sfml_style(int style) {
  switch (style) {
    case j2me::Font::STYLE_PLAIN:
      return sf::Text::Style::Regular;
    case j2me::Font::STYLE_BOLD:
      return sf::Text::Style::Bold;
    case j2me::Font::STYLE_ITALIC:
      return sf::Text::Style::Italic;
    case j2me::Font::STYLE_UNDERLINED:
      return sf::Text::Style::Underlined;
  }
  abort();
}

unsigned int size_to_pixels(int size) {
  switch (size) {
    case j2me::Font::SIZE_MEDIUM:
      return 10;
    case j2me::Font::SIZE_SMALL:
      return 8;
    case j2me::Font::SIZE_LARGE:
      return 12;
  }
  abort();
}

const std::string font_file{"../res/fonts/Skranji-Regular.ttf"};
} // namespace


namespace j2me {

Font::Font(int face, int style, int size)
  : face_(face)
  , style_(to_sfml_style(style))
  , size_(size_to_pixels(size)) {
  const std::string path{"../res/" + font_file};
  if (!font_.loadFromFile(path)) {
    throw std::runtime_error{std::string{"Unable to load: "} + path};
  }
}

Font Font::getFont(int face, int style, int size) {
  return Font{face, style, size};
}

Font Font::getDefaultFont() {
  static std::unique_ptr<Font> font;
  if (!font) {
    font = std::make_unique<Font>(j2me::Font::FACE_SYSTEM, j2me::Font::STYLE_PLAIN, j2me::Font::SIZE_SMALL);
  }
  return *font;
}

int Font::getHeight() const {
  return size_;
}

int Font::getWidth(char c) const {
  auto glyph = font_.getGlyph(c, getHeight(), false);
  return static_cast<int>(glyph.advance);
}

sf::Text::Style Font::style() const {
  return style_;
}

unsigned int Font::size() const {
  return size_;
}

} // namespace j2me
