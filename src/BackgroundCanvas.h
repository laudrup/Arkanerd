#pragma once

#include "j2me/Canvas.h"
#include "j2me/Graphics.h"
#include "j2me/TiledLayer.h"

namespace arkanerd {

class BackgroundCanvas : public j2me::Canvas {

public:
  BackgroundCanvas(j2me::MIDlet* midlet);
  virtual ~BackgroundCanvas() = default;

protected:
  virtual void paint(j2me::Graphics* g) override;

private:
  std::unique_ptr<j2me::TiledLayer> bg_layer_;
};

} // namespace arkanerd
