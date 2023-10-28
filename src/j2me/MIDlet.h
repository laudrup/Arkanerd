#pragma once

#include "Display.h"

namespace j2me {

class MIDlet {
public:
  virtual ~MIDlet() = default;
  int run();

private:
  friend Display;
  Display display_;
};

} // namespace j2me
