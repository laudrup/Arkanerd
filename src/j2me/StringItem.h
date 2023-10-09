#include "Font.h"
#include "Item.h"

#include <optional>
#include <string>

namespace j2me {
class Font;

class StringItem : public Item {
public:
  StringItem(const std::optional<std::string>& label, const std::optional<std::string>& text);
  void setFont(const Font& font);

private:
  friend class Form;
  std::optional<std::string> label_;
  std::optional<std::string> text_;
  Font font_;
};

} // namespace j2me
