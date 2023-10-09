#pragma once

namespace j2me {
class Item {
public:
  virtual ~Item() = default;
  void setLayout(int /*layout*/) {
  }

  inline static constexpr int LAYOUT_DEFAULT = 0;
  inline static constexpr int LAYOUT_LEFT = 1;
  inline static constexpr int LAYOUT_RIGHT = 2;
  inline static constexpr int LAYOUT_CENTER = 3;
  inline static constexpr int LAYOUT_TOP = 0x10;
  inline static constexpr int LAYOUT_BOTTOM = 0x20;
  inline static constexpr int LAYOUT_VCENTER = 0x30;
  inline static constexpr int LAYOUT_NEWLINE_BEFORE = 0x100;
  inline static constexpr int LAYOUT_NEWLINE_AFTER = 0x200;
  inline static constexpr int LAYOUT_SHRINK = 0x400;
  inline static constexpr int LAYOUT_EXPAND = 0x800;
  inline static constexpr int LAYOUT_VSHRINK = 0x1000;
  inline static constexpr int LAYOUT_VEXPAND = 0x2000;
  inline static constexpr int LAYOUT_2 = 0x4000;
  inline static constexpr int PLAIN = 0;
  inline static constexpr int HYPERLINK = 1;
  inline static constexpr int BUTTON = 2;
};
} // namespace j2me
