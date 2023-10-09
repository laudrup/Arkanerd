#pragma once

#include "Display.h"

namespace j2me {

class MIDlet {
public:
  virtual ~MIDlet() = default;
  int run();
  void notifyDestroyed();

protected:
  virtual void startApp() = 0;
  virtual void destroyApp(bool unconditional) = 0;

private:
  friend Display;
  Display display_;
};

} // namespace j2me
