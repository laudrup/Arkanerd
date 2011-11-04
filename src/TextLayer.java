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

package arkanerd;

import java.io.IOException;

import javax.microedition.lcdui.Image;
import javax.microedition.lcdui.game.TiledLayer;

public class TextLayer extends TiledLayer {

	//private final String FONT_FILE = "font.png";
	public static final int WIDTH = 16;
	public static int HEIGHT = 16;
	//private Hashtable chars;
	private final String CHARS = "abcdefghijklmnopqrstuvwxyz 0123456789!;:'-_?";
		
		//{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
		//	'r','s','t','u','v','w','x','y','z',' ','0','1','2','3','4','5',
		//	'6','7','8','9','!',';',':','\'','-','_','?'};
	
	public TextLayer(String text, int max_width) throws IOException {
		super(Math.min(text.length(), max_width), (text.length() / max_width) + 1, Image.createImage("/images/font.png"), 16, 16);
		int row = 0;
		for (int i=0; i<text.length(); i++) {
			setCell(i - (max_width * row),row,CHARS.indexOf(text.substring(i, i+1)) + 1);
			if(((i + 1) % max_width) == 0) row++;
		}
	}	
}
