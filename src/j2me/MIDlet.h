#pragma once

#include "Display.h"

#include "../ResourceManager.h"

namespace j2me {

class MIDlet {
public:
  virtual ~MIDlet() = default;
  int run();

  arkanerd::ResourceManager resources;

private:
  friend Display;
  Display display_;
};

} // namespace j2me
