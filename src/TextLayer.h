#pragma once

/*
  TextLayer.java

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

#include "j2me/TiledLayer.h"

#include <string>

namespace arkanerd {
class TextLayer : public j2me::TiledLayer {
public:
  TextLayer(const std::string &text, int max_width);

  static constexpr int WIDTH = 16;
  static constexpr int HEIGHT = 16;
  //private Hashtable chars;
private:
  const std::string chars_ = "abcdefghijklmnopqrstuvwxyz 0123456789!;:'-_?";

		//{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
		//	'r','s','t','u','v','w','x','y','z',' ','0','1','2','3','4','5',
		//	'6','7','8','9','!',';',':','\'','-','_','?'};

};
} // namespace arkanerd
