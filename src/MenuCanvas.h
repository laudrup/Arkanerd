#pragma once

#include "BackgroundCanvas.h"
#include "ShadowText.h"

#include "j2me/Graphics.h"

#include <functional>
#include <string>
#include <variant>
#include <vector>

namespace arkanerd {

class MenuCanvas : public BackgroundCanvas {

public:
  struct Entry {
    std::string name;
    std::function<void()> on_selected;
  };
  MenuCanvas(j2me::MIDlet* midlet, const std::string& title, const std::vector<Entry>& entries, std::function<void()> on_dismiss);
  void keyPressed(sf::Keyboard::Key key) final;
  MenuCanvas(const MenuCanvas&) = delete;
  MenuCanvas& operator=(const MenuCanvas&) = delete;

protected:
  void paint(j2me::Graphics* g) final;

private:
  std::function<void()> on_dismiss_;
  sf::Font* font_;
  ShadowText title_;
  std::vector<Entry> entries_;
  std::vector<Entry>::iterator selected_;
};

} // namespace arkanerd
