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

package arkanerd;

import java.io.IOException;

import javax.microedition.lcdui.Image;
import javax.microedition.lcdui.game.Sprite;


public class Ball extends Sprite {

	private int x_dir, y_dir, width;//, height;
	private boolean sticky;

	public Ball(ArkanerdCanvas canvas) throws IOException {
		super(Image.createImage("/images/ball.png"));
		width = canvas.getWidth();
		sticky = true;
	}

	//TODO: Set ball to start position
	public void reset() {
	}

	public void setSticky(boolean b) {
		sticky = b;
	}

	public boolean isSticky() {
		return sticky;
	}

	public void setAngle(int x_angle, int y_angle) {
		x_dir = x_angle;
		y_dir = y_angle;
	}

	public void reverseX() {
		x_dir = -x_dir;
	}

	public void reverseY() {
		y_dir = -y_dir;
	}

	public void update() {
		if(getX() >= width - ArkanerdCanvas.FRAME_WIDTH - getWidth() || getX() <= ArkanerdCanvas.FRAME_WIDTH) reverseX();
		if(getY() < ArkanerdCanvas.FRAME_TOP) reverseY();
		if (!sticky)
			move(x_dir, y_dir); //sy += y_dir;
	}
}
