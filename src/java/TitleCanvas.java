/*
  TitleCanvas.java

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
import java.io.InputStream;

import javax.microedition.lcdui.Canvas;
import javax.microedition.lcdui.Font;
import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.Image;
import javax.microedition.lcdui.game.TiledLayer;
import javax.microedition.media.Manager;
import javax.microedition.media.MediaException;
import javax.microedition.media.Player;
import javax.microedition.media.PlayerListener;

public class TitleCanvas extends Canvas implements PlayerListener {

    private int width, height;
    private Main main;
    private TextLayer text;
    private Font f;
    private final String S1 =  "Kasper Laudrup";
    private final String S2 =  "Copyright (c) 2006/7";
    private Image bgImage;
    private TiledLayer bgLayer;
    private Player player;

    public TitleCanvas(Main main) {
        super();
        this.main = main;
        setFullScreenMode(true);
        width = getWidth();
        height = getHeight();
        f = Font.getFont(Font.FACE_SYSTEM,
                         Font.STYLE_PLAIN, Font.SIZE_SMALL);
        try {
            text = new TextLayer("arkanerd", 8);
            bgImage = Image.createImage("/images/titlebg.png");
        } catch (IOException e) {}
        text.setPosition((width - text.getWidth())/2,
                         (height - text.getHeight())/2);
        int rows = (height/bgImage.getHeight()) + 1;
        bgLayer = new TiledLayer(1, rows, bgImage, bgImage.getWidth(), bgImage.getHeight());
        bgLayer.fillCells(0,0,1,rows,1);
        try {
            InputStream ins = getClass().getResourceAsStream("/music/intro.mid" );
            player = Manager.createPlayer(ins, "audio/midi");
            player.addPlayerListener(this);
            player.start();
        } catch (MediaException pe) {
            System.err.println(pe.getMessage());
        } catch (IOException ioe) {
            System.err.println(ioe.getMessage());
        }
    }

    protected void paint(Graphics g) {
        bgLayer.paint(g);
        text.paint(g);
        g.setColor(0x00000000);
        g.drawString(S1, width /2,
                     height / 2 + height /4,
                     Graphics.TOP | Graphics.HCENTER);
        g.drawString(S2, width /2,
                     height /2 + height /4 + f.getHeight(),
                     Graphics.TOP | Graphics.HCENTER);
        g.setColor(0x00DD2222);
        g.drawString(S1, width /2,
                     (height / 2 + height /4) + 2,
                     Graphics.TOP | Graphics.HCENTER);
        g.drawString(S2, width /2,
                     (height /2 + height /4 + f.getHeight()) + 2,
                     Graphics.TOP | Graphics.HCENTER);
    }

    public void playerUpdate(Player player, String event, Object data) {
        if (event == END_OF_MEDIA) {
            try {
                player.stop();
                player.close();
            } catch (MediaException e) {}
            main.showMenu();
        }
    }

    protected void keyPressed(int key) {
        try {
            player.stop();
            player.close();
        } catch (MediaException e) {}
        main.showMenu();
    }
}
