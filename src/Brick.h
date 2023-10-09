#pragma once

/*
  Brick.java

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

#include "j2me/Sprite.h"

namespace arkanerd {
class Brick : public j2me::Sprite {
public:
  Brick() = default;
  Brick(int color, int type);
  int getType();
		//public static final int BLUE = 1;
		//public static final int GREEN = 2;
		//public static final int PURPLE = 3;
		//public static final int BONUS = 10;
		//private static Image image;
		//public static final int BONUS = 1;
private:
  int type_ = 0;

		//private static Image getImage() throws IOException {
		//if (image == null) {
		//System.err.println("New image");
		//image = Image.createImage("/images/bricks.png");
		//}
		//return image;
		//}
};
}
