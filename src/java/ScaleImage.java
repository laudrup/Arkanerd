/* Copyright (c) 2002,2003, Stefan Haustein, Oberhausen, Rhld., Germany
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The  above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE. */

package arkanerd;

import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.Image;




/** This class provides a single static method that allows to scale an image */


public class ScaleImage {

    /**
     * Creates a new, scaled version of the given image.
     *
     * @param src: The source image
     * @param dstW: The destination (scaled) image width
     * @param dstH: The destination (scaled) image height
     * @return Image: A new Image object with the given width and height.
     */

    public static Image scaleImage (Image src, int dstW, int dstH) {
        int srcW = src.getWidth();
        int srcH = src.getHeight();

        Image tmp = Image.createImage(dstW, srcH);
        Graphics g = tmp.getGraphics();

        int delta = (srcW << 16) / dstW;
        int pos = delta/2;

        for (int x = 0; x < dstW; x++) {
            g.setClip(x, 0, 1, srcH);
            g.drawImage(src, x - (pos >> 16), 0, Graphics.LEFT | Graphics.TOP);
            pos += delta;
        }

        Image dst = Image.createImage(dstW, dstH);
        g = dst.getGraphics();

        delta = (srcH << 16) / dstH;
        pos = delta/2;

        for (int y = 0; y < dstH; y++) {
            g.setClip(0, y, dstW, 1);
            g.drawImage(tmp, 0, y - (pos >> 16), Graphics.LEFT | Graphics.TOP);
            pos += delta;
        }

        return dst;
    }
}
