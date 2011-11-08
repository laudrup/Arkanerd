/*
  Level.java

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
import java.util.Enumeration;
import java.util.Vector;

public class Level {
    private int bricks_x, bricks_y, num_bricks;
    private Vector bricks;
    private String name;
    private boolean[] empty;

    // Number of bricks _excluding_ empty (Actual number of images in this level)
    public int getNumBricks() {
        return num_bricks;
    }

    // Number of rows _including_ empty
    public int getBricks_x() {
        return bricks_x;
    }

    // Number of lines _including_ empty
    public int getBricks_y() {
        return bricks_y;
    }

    public String getName() {
        return name;
    }

    public Level(int num) {
        bricks_x = 0;
        bricks_y = 0;
        num_bricks = 0;
        name = "";
        Vector lines = readFile("/levels/level" + num + ".txt");
        parseLevelFile(lines);
    }

    public boolean isEmpty(int i) {
        return empty[i];
    }

    public Vector getBricks() {
        return bricks;
    }

    private void parseLevelFile(Vector lines) {
        String line ="";
        int color, type;
        int count = 0;
        Brick brick;
        bricks = new Vector();
        System.err.println("Elements: " + lines.size());
        //XXX: First parse non-brick lines
        for (Enumeration e = lines.elements(); e.hasMoreElements();
             line = (String)e.nextElement()) {
            if(line.startsWith("#")) {
                continue; // Skip comments
            }
            else if(line.startsWith("Name")) {
                name = line.substring(5);
                System.err.println(name);
            }
            else {
                // The definition of a brick is 2 chars
                bricks_x = line.length() / 2;
                bricks_y++;
            }
        }
        // Then get the brick definitions
        empty = new boolean[bricks_x * bricks_y];
        for (Enumeration e = lines.elements(); e.hasMoreElements();) {
            line = (String)e.nextElement();
            if(line.startsWith("#") ||
               line.startsWith("Name")) {
                continue;
            }
            else {
                for(int i = 0; i < line.length(); i += 2) {
                    color = Integer.parseInt(line.substring(i, i + 1));
                    type = Integer.parseInt(line.substring(i + 1, i + 2));
                    if(color == 0) {
                        empty[count] = true;
                    } else {
                        try {
                            brick = new Brick(color, type);
                            bricks.addElement(brick);
                        } catch(IOException ioe) {}
                        num_bricks++;
                    }
                    count++;
                }
            }
        }
    }

    private Vector readFile(String fname) {
        StringBuffer str;
        Vector lines = new Vector();
        try {
            InputStream is = this.getClass().getResourceAsStream(fname);
            str = new StringBuffer();
            byte[] b = new byte[1];
            while(is.read(b) != -1) {
                if(b[0] == '\n') {
                    lines.addElement(new String(str));
                    str = new StringBuffer();
                } else {
                    str.append(new String(b));
                }
            }
            is.close();
        } catch(IOException e) {
            System.err.println("Could not read from file: " + e.getMessage());
            return null;
        }
        return lines;
    }
}
