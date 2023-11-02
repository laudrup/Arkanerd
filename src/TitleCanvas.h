#pragma once

#include "TextLayer.h"
#include "BackgroundCanvas.h"

#include "j2me/Font.h"
#include "j2me/Graphics.h"

#include <functional>
#include <string>

namespace arkanerd {

class TitleCanvas : public BackgroundCanvas {

public:
  TitleCanvas(j2me::MIDlet* midlet, std::function<void()> on_dismiss);
  void keyPressed(sf::Keyboard::Key key) final;

protected:
  void paint(j2me::Graphics* g) final;

private:
  std::function<void()> on_dismiss_;
  std::unique_ptr<TextLayer> text_;
  j2me::Font f_;
  const std::string S1_ = "Kasper Laudrup";
  const std::string S2_ = "Copyright (c) 2006/7";
};

} // namespace arkanerd
