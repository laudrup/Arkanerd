/* 
    BonusBrick.java 

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

public class BonusBrick extends Sprite {
	public static final int NO_BONUS = 0;
	public static final int POINT_BONUS = 1;
	public static final int STICKY_BONUS = 2;
	public static final int BREAK_BONUS = 3;
	public static final int LIVE_BONUS = 4;
	private int type;
	
	public BonusBrick(int type) throws IOException {
		super(Image.createImage("/images/bonus" + type + ".png"), 20, 10);
		this.type = type; 
	}
	
	public int getType() {
		return type;
	}
}
