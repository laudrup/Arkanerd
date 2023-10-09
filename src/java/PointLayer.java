/*
  PointLayer.java

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

public class PointLayer extends TiledLayer {

    private int number;
    private int digits;
    private String text;
    private final String CHARS = "abcdefghijklmnopqrstuvwxyz 0123456789!;:'-_?";

    public PointLayer(int digits) throws IOException {
        super(digits, 1, Image.createImage("/images/font.png"), 16, 16);
        for (int i=0; i < digits; i++) {
            setCell(i,0,CHARS.indexOf("0") + 1);
        }
        this.digits = digits;
        number = 0;
        text = new String();
    }

    public void setNum(int num) {
        number = num;
        text = String.valueOf(number);
        for (int i=0; i<text.length(); i++) {
            setCell(digits-text.length()+i,0,CHARS.indexOf(text.substring(i, i+1)) + 1);
        }
    }

    public void add(int amount) {
        number += amount;
        text = String.valueOf(number);
        for (int i=0; i<digits; i++) {
            setCell(i,0,CHARS.indexOf(text.substring(i, i+1)) + 1);
        }
    }
}
