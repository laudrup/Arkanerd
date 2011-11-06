/*
    Bricks.java

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

import java.util.Enumeration;
import java.util.Vector;

import javax.microedition.lcdui.game.Sprite;


public class Bricks {

	private Vector bricks;
	private Level level;
	private Brick brick;
	private int width, num_bricks, bricks_left;

	public Bricks(ArkanerdCanvas canvas, Level level) {
		width = canvas.getWidth();
		this.level = level;
		loadBricks();
		bricks_left = bricks.size();
	}

	private void loadBricks() {
		// Place the bricks on the canvas as defined in level
		num_bricks = level.getNumBricks();
		bricks = level.getBricks();
		int x_pos = (width - 20 * level.getBricks_x()) / 2;
		int y_pos = ArkanerdCanvas.FRAME_TOP + ArkanerdCanvas.FRAME_WIDTH;
		int count = 0;
		// Place the bricks according to the level definition
		Enumeration e = bricks.elements();
		brick = (Brick)e.nextElement();
		for(int y=0; y < level.getBricks_y(); y++) {
			for(int x=0; x < level.getBricks_x(); x++) {
				if(!level.isEmpty(count)) {
					brick.setPosition(x_pos,y_pos);
					if(e.hasMoreElements()) brick = (Brick)e.nextElement();
				}
				x_pos += brick.getWidth();
				count++;
			}
			x_pos = (width - 20 * level.getBricks_x()) / 2;
			y_pos += brick.getHeight();
		}
		bricks_left = num_bricks;
	}

	public Vector getBricks() {
		return bricks;
	}

	public int getBricksLeft() {
		return bricks_left;
	}

	public int getNumBricks() {
		return num_bricks;
	}

	public Brick getBrick(int i) {
		return (Brick)bricks.elementAt(i);
	}

	// Get the last hit brick
	public Brick getBrick() {
		return brick;
	}

	public boolean checkCollisions(Sprite sprite) {
		for(Enumeration e = bricks.elements(); e.hasMoreElements();
	    brick = (Brick)e.nextElement()) {
			if(brick.collidesWith(sprite, false)) {
				brick.setVisible(false);
				bricks_left--;
				return true;
			}
		}
		return false;
	}
}
