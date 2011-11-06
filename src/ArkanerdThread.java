/*
    ArkanerdThread.java

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

public class ArkanerdThread extends Thread {

	private boolean pause;
	private boolean stop;
	private ArkanerdCanvas canvas;

	ArkanerdThread(ArkanerdCanvas canvas) {
		this.canvas = canvas;
	}

	void pause() {
		pause = true;
	}

	synchronized void resumeGame() {
		pause = false;
		notify();
	}

	synchronized void stop() {
		stop = true;
		notify();
	}

	public void run() {
	// Flush any keystrokes that occurred before the
	// game started:
		canvas.flushKeys();
		canvas.setThread(this);
		canvas.nextLevel();
		stop = false;
		while(true) {
			if(stop) {
				break;
			}
			while(pause) {
					try {
					wait();
				} catch(Exception e) {}
			}
		  canvas.render();
	      canvas.input();
	      canvas.update();
	      canvas.checkCollisions();
	      // You do a short pause to allow the other thread
	      // to update the information about which keys are pressed:
	      synchronized(this) {
	    	  try {
	    		  wait(1);
	    	  } catch(Exception e) {}
	      }
		}
	}
}
