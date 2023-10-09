#pragma once

#include "Item.h"
#include "Image.h"

#include <string>

namespace j2me {

class ImageItem : public Item {
public:
  ImageItem(const std::string& label, const Image& img, int layout, const std::string& altText);

private:
  friend class Form;
  const std::string label_;
  Image img_;
  int layout_;
};

} // namespace j2me
