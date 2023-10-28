#pragma once

#include "TextLayer.h"

#include "j2me/Canvas.h"
#include "j2me/Font.h"
#include "j2me/Graphics.h"

#include <functional>
#include <string>

namespace arkanerd {

class TitleCanvas : public j2me::Canvas {

public:
  TitleCanvas(j2me::MIDlet* midlet, std::function<void()> on_dismiss);
  void keyPressed(int key) final;

protected:
  void paint(j2me::Graphics* g) final;

private:
  std::function<void()> on_dismiss_;
  std::unique_ptr<TextLayer> text_;
  j2me::Font f_;
  const std::string S1_ = "Kasper Laudrup";
  const std::string S2_ = "Copyright (c) 2006/7";
  std::unique_ptr<j2me::TiledLayer> bg_layer_;
};

}
