#pragma once

#include "TextLayer.h"

#include "j2me/Canvas.h"
#include "j2me/Font.h"
#include "j2me/Image.h"
#include "j2me/Player.h"
#include "j2me/PlayerListener.h"
#include "j2me/Graphics.h"

#include <string>
#include <any>

/*
  TitleCanvas.java

  Arkanerd - An Arkanoid/Breakout like game for J2ME mobile phones
  Copyright (C) 2006  Kasper Laudrup

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

namespace arkanerd {
class Main;

class TitleCanvas : public j2me::Canvas, public j2me::PlayerListener {

public:
  TitleCanvas(Main* main);
  void playerUpdate(const j2me::Player* player, const std::string& event, const char* data) override;
  void keyPressed(int key) override;

protected:
  void paint(j2me::Graphics* g) override;

private:
  int width_ = 0;
  int height_ = 0;
  Main* main_;
  TextLayer* text_;
  j2me::Font f_;
  const std::string S1_ = "Kasper Laudrup";
  const std::string S2_ = "Copyright (c) 2006/7";
  j2me::Image bg_image_;
  j2me::TiledLayer* bg_layer_;
  j2me::Player player_;
};

}
