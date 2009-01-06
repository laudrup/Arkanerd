/* 
    LivesLayer.java 

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
import javax.microedition.lcdui.game.TiledLayer;

public class LivesLayer extends TiledLayer {

	private String text;
	private final String CHARS = "abcdefghijklmnopqrstuvwxyz 0123456789!;:'-_?";

	public LivesLayer(int lives) throws IOException {
		super(5, 1, Image.createImage("/images/font.png"), 16, 16);
		text = new String();
		update(lives);	
	}
	
	public void update(int lives) {
			// Clear the collumns
			fillCells(0,0,5,1,0);
			// Fill in the hearts
			for (int i=2;  i < lives + 2 && i < getColumns(); i++) {
				setCell(i,0,47);
			}
			if (lives > 3) { 
			// Fill in the number of lives
			text = String.valueOf(lives);
			if (lives > 9) {
				setCell(0,0,CHARS.indexOf(text.substring(0, 1)) + 1);
				setCell(1,0,CHARS.indexOf(text.substring(1, 2)) + 1);
			} else {
				setCell(1,0,CHARS.indexOf(text.substring(0, 1)) + 1);
			}
		}
	}
}
