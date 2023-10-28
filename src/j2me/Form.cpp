#include "Form.h"
#include "Displayable.h"
#include "Font.h"
#include "Graphics.h"
#include "ImageItem.h"
#include "StringItem.h"

namespace {
std::string wrap_text(std::string str, const j2me::Font& font, int width) {
  size_t last_space = 0;
  int line_width = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == '\n') {
      line_width = 0;
      continue;
    }
    if (str[i] == ' ') {
      last_space = i;
    }
    line_width += font.getWidth(str[i]);
    if (line_width > width) {
      str[last_space] = '\n';
      line_width = 0; // TODO: Recalculate actual width
    }
  }
  return str;
}
} // namespace

namespace j2me {

Form::Form(MIDlet* midlet, const std::string& title)
  : Displayable(midlet)
  , title_(title) {
}

int Form::append(std::unique_ptr<Item> item) {
  items_.push_back(std::move(item));
  return static_cast<int>(items_.size());
}

int Form::append(const std::string& str) {
  return append(std::make_unique<StringItem>(std::nullopt, str));
}

void Form::handleKey(sf::Keyboard::Key key) {
  Displayable::handleKey(key);
}

void Form::handlePaint(Graphics* g) {
  auto font = Font::getFont(Font::FACE_SYSTEM, Font::STYLE_PLAIN, Font::SIZE_LARGE);
  g->setFont(font);
  g->drawString(title_, 0, 10, Graphics::TOP | Graphics::VCENTER);
  int y = font.getHeight() + 10;
  font = Font::getFont(Font::FACE_SYSTEM, Font::STYLE_PLAIN, Font::SIZE_SMALL);
  g->setFont(font);
  for (const auto& item : items_) {
    auto string_item = dynamic_cast<StringItem*>(item.get());
    if (string_item != nullptr && string_item->text_) {
      const auto text = wrap_text(*string_item->text_, font, static_cast<int>(g->target_->getView().getSize().x) - 10);
      g->drawString(text, 5, y, Graphics::TOP | Graphics::LEFT);
      const auto lines = static_cast<int>(std::count(text.begin(), text.end(), '\n')) + 1;
      y += lines * (font.getHeight() + 3);
    }
    auto image_item = dynamic_cast<ImageItem*>(item.get());
    if (image_item != nullptr) {
      g->drawImage(image_item->img_, 5, y, 0);
      y += image_item->img_.getHeight() + 5;
    }
  }
}

} // namespace j2me
