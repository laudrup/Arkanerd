#include "ImageItem.h"

namespace j2me {

ImageItem::ImageItem(const std::string& label, const Image& img, int layout, const std::string& /*altText*/)
  : label_(label)
  , img_(img)
  , layout_(layout) {
}

} // namespace j2me
