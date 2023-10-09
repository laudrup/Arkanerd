#include "StringItem.h"

namespace j2me {

StringItem::StringItem(const std::optional<std::string> &label, const std::optional<std::string> &text)
  : label_(label)
  , text_(text)
  , font_(Font::getDefaultFont()) {
}

void StringItem::setFont(const Font& font) {
  font_ = font;
}

} // namespace j2me
