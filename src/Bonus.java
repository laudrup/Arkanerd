/*
    Bonus.java

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
import java.util.Enumeration;
import java.util.Vector;

import javax.microedition.lcdui.game.LayerManager;
import javax.microedition.lcdui.game.Sprite;

public class Bonus {
	//private Image image;
	private BonusBrick bonusBrick;
	private Vector bonusBricks;
	private LayerManager layerManager;
	private ArkanerdCanvas canvas;

	public Bonus(LayerManager layerManager, ArkanerdCanvas canvas) {
		this.layerManager = layerManager;
		this.canvas = canvas;
		bonusBricks = new Vector();
	}

	public void addBonus(int x, int y, int type) {
		try {
			bonusBrick = new BonusBrick(type);
		} catch (IOException e) {}
		bonusBrick.setPosition(x, y);
		layerManager.insert(bonusBrick, 3);
		bonusBricks.addElement(bonusBrick);
	}

	public void clear() {
		for(Enumeration e = bonusBricks.elements(); e.hasMoreElements();) {
			bonusBrick = (BonusBrick)e.nextElement();
			bonusBrick.setVisible(false);
		}
		bonusBricks.removeAllElements();
	}

	public void update() {
		for(Enumeration e = bonusBricks.elements(); e.hasMoreElements();) {
			bonusBrick = (BonusBrick)e.nextElement();
			bonusBrick.setPosition(bonusBrick.getX(), bonusBrick.getY() + 1);
			bonusBrick.nextFrame();
	        if(bonusBrick.getY() > canvas.getHeight())
	        	bonusBricks.removeElement(bonusBrick);
		}
	}

	// Return the type of the last bonus hit
	public int getType() {
		return bonusBrick.getType();
	}

	public boolean checkCollisions(Sprite sprite) {
		for(Enumeration e = bonusBricks.elements(); e.hasMoreElements();) {
			bonusBrick = (BonusBrick)e.nextElement();
	        if(bonusBrick.collidesWith(sprite, false)) {
	        	bonusBrick.setVisible(false);
	        	bonusBricks.removeElement(bonusBrick);
				return true;
	         	}
			}
		return false;
	}

}
