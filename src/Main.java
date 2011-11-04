/* 
    Main.java 

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

import javax.microedition.lcdui.Choice;
import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Font;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.Image;
import javax.microedition.lcdui.ImageItem;
import javax.microedition.lcdui.Item;
import javax.microedition.lcdui.List;
import javax.microedition.lcdui.StringItem;
import javax.microedition.lcdui.game.Sprite;
import javax.microedition.midlet.MIDlet;

public class Main extends MIDlet implements CommandListener {

	private Display display;
	private TitleCanvas titleCanvas;
	private Settings settings;
	private ArkanerdCanvas arkanerdCanvas;
	private ArkanerdThread arkanerdThread;
	private List settings_menu;

	static final Command BACK_COMMAND = new Command("Back", Command.BACK, 0);
	static final Command EXIT_COMMAND = new Command("Exit", Command.EXIT, 1);
	static final Command SAVE_COMMAND = new Command("Save", Command.SCREEN, 2);

	public Main() {
		display = Display.getDisplay(this);
		settings = new Settings();
	}

	protected void destroyApp(boolean b) {
		System.err.println("Game exit...");
		//XXX: Clean up, or maybe even save state
	}

	protected void pauseApp() {
		if (arkanerdThread != null)
			arkanerdThread.pause();
	}

	protected void startApp() {
		titleCanvas = new TitleCanvas(this);
		display.setCurrent(titleCanvas);
	}

	public void commandAction(Command cmd, Displayable dsp) {
		if(cmd.getCommandType() == Command.EXIT) {
			destroyApp(true);
			notifyDestroyed();
		}
		else if(cmd.getCommandType() == Command.BACK) {
			showMenu();
		}
		else if(cmd == SAVE_COMMAND) {
			boolean selected[] = new boolean[settings_menu.size()];
			// Fill array indicating whether each element is checked 
			settings_menu.getSelectedFlags(selected);
			settings.setMusic(selected[0]);
			settings.saveConfig();
			showMenu();
		}
		else {
			List menu = (List)display.getCurrent();
			switch(menu.getSelectedIndex()) {
			case 0:
				newGame();
				break;
			case 1:
				instructions();
				break;
			case 2:
				highScores();
				break;
			case 3:
				settings();
				break;
			case 4:
				about();
				break;
			}
		}
	}

	public void showMenu() {
		String[] menuItems = {"New game", "Instructions", "High Scores", "Settings", "About"};
		List menu = new List("Arkanerd", Choice.IMPLICIT, menuItems, null);
		menu.addCommand(EXIT_COMMAND);
		menu.setCommandListener(this);
		display.setCurrent(menu);
	}
	
	public void gameComplete(int points) {
		if (arkanerdThread != null)
			arkanerdThread.stop();
		Form gameCompleteForm = new Form("Game completed!");
		StringItem gameOverString = new StringItem(null, "You did it!\n");
		gameOverString.setFont(Font.getFont(Font.FACE_MONOSPACE, Font.STYLE_BOLD, Font.SIZE_LARGE));
		StringItem s1 = new StringItem(null, "You completed all leves!");
		StringItem s2 = new StringItem(null, "Please go to http://www.linuxfan.dk");
		StringItem s3 = new StringItem(null, "To look for more levels");
		gameOverString.setLayout(Item.LAYOUT_CENTER);
		s1.setLayout(Item.LAYOUT_CENTER);
		s2.setLayout(Item.LAYOUT_CENTER);
		s3.setLayout(Item.LAYOUT_CENTER);
		gameCompleteForm.append(gameOverString);
		gameCompleteForm.append(s1);
		gameCompleteForm.append(s2);
		gameCompleteForm.append(s3);
		showScoreString(points, gameCompleteForm);
		gameCompleteForm.addCommand(BACK_COMMAND);
		gameCompleteForm.setCommandListener(this);
		display.setCurrent(gameCompleteForm);
	}
	
	public void gameOver(int points) {
		if (arkanerdThread != null)
			arkanerdThread.stop();
		Form gameOverForm = new Form("Game over!");
		StringItem deadString = new StringItem(null, "Game over!\n");
		deadString.setFont(Font.getFont(Font.FACE_MONOSPACE, Font.STYLE_BOLD, Font.SIZE_LARGE));
		deadString.setLayout(Item.LAYOUT_CENTER);
		gameOverForm.append(deadString);
		showScoreString(points, gameOverForm);
		gameOverForm.addCommand(BACK_COMMAND);
		gameOverForm.setCommandListener(this);
		display.setCurrent(gameOverForm);
	}

	private void newGame() {
		arkanerdCanvas = new ArkanerdCanvas(this, settings);
		arkanerdThread = new ArkanerdThread(arkanerdCanvas);
		display.setCurrent(arkanerdCanvas);
		//arkanerdCanvas.musicOn(settings.musicOn());
        arkanerdThread.start();
	}
	
	private void showScoreString(int score, Form form) {
		if (score > settings.getHighScore()) {
			settings.setHighScore(score);
			settings.saveConfig();
			StringItem s1 = new StringItem(null, "Congratulations!\n");
			StringItem s2 = new StringItem(null, "You got a new High Score:\n");
			StringItem s3 = new StringItem(null, String.valueOf(score));
			s1.setLayout(Item.LAYOUT_CENTER);
			s2.setLayout(Item.LAYOUT_CENTER);
			s3.setLayout(Item.LAYOUT_CENTER);
			form.append(s1);
			form.append(s2);
			form.append(s3);
		} else {
		StringItem s1 = new StringItem(null, "Your Score:\n");
		StringItem s2 = new StringItem(null, String.valueOf(score) + "\n");
		StringItem s3 = new StringItem(null, "High Score:\n");
		StringItem s4 = new StringItem(null, String.valueOf(settings.getHighScore()));
		s1.setLayout(Item.LAYOUT_CENTER);
		s2.setLayout(Item.LAYOUT_CENTER);
		s3.setLayout(Item.LAYOUT_CENTER);
		s4.setLayout(Item.LAYOUT_CENTER);
		form.append(s1);
		form.append(s2);
		form.append(s3);
		form.append(s4);
		}
	}
	
	private void settings() {
		settings_menu = new List("Settings", List.MULTIPLE);
		settings_menu.append("Enable Music", null);
		settings_menu.setSelectedIndex(0, settings.musicOn());
		settings_menu.setCommandListener(this); 
		settings_menu.addCommand(BACK_COMMAND);
		settings_menu.addCommand(SAVE_COMMAND);
		settings_menu.setCommandListener(this);
		display.setCurrent(settings_menu);
	}
	
	private void highScores() {
		Form highScoreForm = new Form("High Score");
		StringItem highString = new StringItem(null, "High score: " + settings.getHighScore());
		highString.setLayout(Item.LAYOUT_CENTER);
		highScoreForm.append(highString);
		highScoreForm.addCommand(BACK_COMMAND);
		highScoreForm.setCommandListener(this);
		display.setCurrent(highScoreForm);
	}
	
	private void instructions() {
		Form instructionsForm = new Form("Instructions");
		instructionsForm.append(
					 "Arkanerd is a little Arkanoid/Break-out like game.\n\n" +
					 "The goal of the game is to clear out the colored bricks " +
					 "placed in the central part of the screen\n\n" +
					 "This is achieved by bouncing the ball around the screen, which " +
					 "is done by moving the small platform located at the bottom of " +
					 "the screen.\n\n" +
					 "Be careful though, since you have to catch the ball before it " +
					 "leaves the screen, otherwise you lose a life.\n\n" +
					 "Special bricks releases a special bonus when you hit them, which, " +
					 "when \"picked up\" with the player-controlled platform, changes the " +
					 "gameplay in different ways.\n\n" +
					 "The special powerup bonuses are:\n");
		try {
			Image img = Image.createImage(Image.createImage("/images/bonus1.png"), 0, 0, 20, 10, Sprite.TRANS_NONE);
			ImageItem bonus = new ImageItem("100 Points", img, Item.LAYOUT_LEFT | Item.LAYOUT_NEWLINE_AFTER, "");
			instructionsForm.append(bonus);
		} catch (IOException e) {}
		instructionsForm.append("Adds 100 points to the current score.");
		
		try {
			Image img = Image.createImage(Image.createImage("/images/bonus2.png"), 0, 0, 20, 10, Sprite.TRANS_NONE);
			ImageItem bonus = new ImageItem("Sticky ball", img, Item.LAYOUT_LEFT | Item.LAYOUT_NEWLINE_AFTER, "");
			instructionsForm.append(bonus);
		} catch (IOException e) {}
		instructionsForm.append("The ball \"sticks\" to the platform. Press the \"fire\" button to release it.");

		try {
			Image img = Image.createImage(Image.createImage("/images/bonus3.png"), 0, 0, 20, 10, Sprite.TRANS_NONE);
			ImageItem bonus = new ImageItem("Power ball", img, Item.LAYOUT_LEFT | Item.LAYOUT_NEWLINE_AFTER, "");
			instructionsForm.append(bonus);
		} catch (IOException e) {}
		instructionsForm.append("The ball doesn't bounce off the bricks, instead it shoots right through them.");

		try {
			Image img = Image.createImage(Image.createImage("/images/bonus4.png"), 0, 0, 20, 10, Sprite.TRANS_NONE);
			ImageItem bonus = new ImageItem("Extra life", img, Item.LAYOUT_LEFT | Item.LAYOUT_NEWLINE_AFTER, "");
			instructionsForm.append(bonus);
		} catch (IOException e) {}
		instructionsForm.append("Gives you an extra life.\n");
		instructionsForm.append("\n");
		instructionsForm.append("\nEnjoy your time with Arkanerd!");

		instructionsForm.addCommand(BACK_COMMAND);
		instructionsForm.setCommandListener(this);
		display.setCurrent(instructionsForm);	
	}
	
	private void about() {
		Form aboutForm = new Form("About Arkanerd"); 
		String aboutText = 
			"A little Arkanoid/Break-out like game for Java MIDP 2.0\n\n" +
			"Copyright (C) 2006 Kasper Laudrup\n\n" +
			"Arkanerd is free software, covered by the GNU General Public License," +
			" and you are welcome to change it and/or distribute copies of it" +
			" under certain conditions.\n\n" +
			"Please see http://www.linuxfan.dk for source code etc.";
		aboutForm.append(new StringItem(null, aboutText));
		aboutForm.addCommand(BACK_COMMAND);
		aboutForm.setCommandListener(this);
		display.setCurrent(aboutForm);		
	}
}
