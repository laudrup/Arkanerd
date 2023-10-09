#pragma once

/*
  Ball.java

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

class ArkanerdCanvas;

class Ball : public j2me::Sprite {
	public:
		Ball(ArkanerdCanvas *canvas);

		//TODO: Set ball to start position
		void reset();
		void setSticky(bool b);
		bool isSticky();
		void setAngle(int x_angle, int y_angle);
		void reverseX();
		void reverseY();
		void update();

private:
  ArkanerdCanvas* canvas_;
  int x_dir = 0;
  int y_dir = 0;
  int width = 0;
  bool sticky = false;
};

} // namespace arkanerd
