/*
  ArkanerdCanvas.java

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

import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.Image;
import javax.microedition.lcdui.game.GameCanvas;
import javax.microedition.lcdui.game.LayerManager;
import javax.microedition.lcdui.game.TiledLayer;
import javax.microedition.media.Manager;
import javax.microedition.media.Player;


public class ArkanerdCanvas extends GameCanvas {
    private Board board;
    //private Font f;
    private Main main;
    private Ball ball;
    private Bonus bonus;
    private Bricks bricks;
    private Image bgImage;
    private Player player;
    //private boolean music_on;
    private Settings settings;
    private PointLayer pointLayer;
    private LivesLayer livesLayer;
    private TiledLayer bgLayer;
    private TextLayer textLayer;
    private LayerManager layerManager;
    private ArkanerdThread thread;
    private Level level;
    private int current_bonus;
    private int width, height, lives, points, level_num;
    public final static int FRAME_WIDTH = 7;
    public final static int FRAME_TOP = 40; // Vi skal have denne fra et eller andet sted
    public final static int BOARD_SPACE = 20;
    private final int BOARD_SPEED = 5;

    public ArkanerdCanvas(Main main, Settings settings) {
        //XXX: This slows down the game generates keyevents
        super(false);
        setFullScreenMode(true);
        this.main = main;
        this.settings = settings;
        //setCommandListener(main);
        width = getWidth();
        height = getHeight();// - FRAME_TOP;
        level_num = 0;
        lives = 3;
        layerManager = new LayerManager();
        //f = Font.getFont(Font.FACE_MONOSPACE, Font.STYLE_BOLD, Font.SIZE_SMALL);
        try {
            board = new Board();
            ball = new Ball(this);
            pointLayer = new PointLayer(5);
            livesLayer = new LivesLayer(lives);
        } catch (IOException e) {}
        layerManager.append(pointLayer);
        layerManager.append(livesLayer);
        pointLayer.setPosition(20,10);
        livesLayer.setPosition(width - 20 - livesLayer.getWidth(), 10);
        layerManager.append(board);
        layerManager.append(ball);
    }

    //public void musicOn(boolean b) {
    //music_on = b;
    //}

    public void setThread(ArkanerdThread thread) {
        this.thread = thread;
    }

    public void flushKeys() {
        getKeyStates();
    }

    public void dead() {
        //XXX Vibrate doesn't work??
        //Display display = Display.getDisplay(main);
        //display.vibrate(1000);
        if(lives == 0) {
            main.gameOver(points);
        }
        lives--;
        livesLayer.update(lives);
        board.setPosition(width/2 - board.getWidth()/2, height - BOARD_SPACE);
        ball.setPosition(width/2  - ball.getWidth()/2, height - BOARD_SPACE - ball.getHeight());
        bonus.clear();
        // Show start text and pause game
        start();
    }

    private void start() {
        current_bonus = BonusBrick.NO_BONUS;

        //Show the level name
        try {
            textLayer = new TextLayer(level.getName(), width / TextLayer.WIDTH);
        } catch (IOException e) {}
        textLayer.setPosition((width-textLayer.getWidth())/2, (height-textLayer.getHeight())/2);
        layerManager.insert(textLayer, 0);
        layerManager.paint(getGraphics(),0,0);
        flushGraphics();
        if (player != null) {
            try {
                if (player.getState() != Player.STARTED)
                    player.start();
            } catch (Exception e) {}
        }
        thread.pause();
    }

    public void nextLevel() {
        level_num++;
        // Try and load the new level if unsuccesfull, no more levels available
        try {
            level = new Level(level_num);
        } catch (Exception e) {
            main.gameComplete(points);
        }
        if(bonus != null) bonus.clear();
        bonus = new Bonus(layerManager, this);

        //TODO:
        ball.setAngle(2, -3);
        ball.setPosition(width/2  - ball.getWidth()/2, height - BOARD_SPACE - ball.getHeight());

        // Set up the new bricks for this level
        board.setPosition(width/2 - board.getWidth()/2, height - BOARD_SPACE);
        bricks = new Bricks(this, level);
        for(int i=0; i<bricks.getNumBricks(); i++) {
            if(bricks.getBrick(i) != null)
                layerManager.append(bricks.getBrick(i));
        }

        try {
            bgImage = Image.createImage("/levels/level" + level_num + ".png");
        } catch (IOException e) {}
        int rows = (height/bgImage.getHeight()) + 1;
        if(bgLayer != null)
            layerManager.remove(bgLayer);
        bgLayer = new TiledLayer(1, rows, bgImage, bgImage.getWidth(), bgImage.getHeight());
        bgLayer.fillCells(0,0,1,rows,1);
        layerManager.append(bgLayer);

        // Set music for this level (if possible)
        if (settings.musicOn()) {
            System.err.println("Trying to create player");
            try {
                if (player != null && player.getState() == Player.STARTED)
                    player.close();
                InputStream ins = getClass().getResourceAsStream("/levels/level" + level_num + ".mid" );
                player = Manager.createPlayer(ins, "audio/midi");
                player.setLoopCount(-1);
                System.err.println("player started");
            } catch (Exception e) {
                System.err.println("Oops: " + e.getMessage());
                player = null;
            }
        }
        // Clean up
        System.gc();

        // Render the initial graphics
        render();

        // Show start text and pause game
        start();
    }

    public void update() {
        ball.update();
        bonus.update();
        if(ball.getY() > height) dead();
        if(bricks.getBricksLeft() == 0) nextLevel();
    }

    public void input() {
        int keyStates = getKeyStates();
        int currentX = board.getX();
        if ((keyStates & LEFT_PRESSED) != 0) {
            board.setPosition(Math.max(FRAME_WIDTH, currentX-BOARD_SPEED), height-BOARD_SPACE);
            if (ball.isSticky())
                if (currentX-BOARD_SPEED > FRAME_WIDTH)
                    ball.move(-BOARD_SPEED, 0);
        }
        if ((keyStates & RIGHT_PRESSED) != 0) {
            board.setPosition(Math.min(width-FRAME_WIDTH-board.getWidth(), currentX+BOARD_SPEED), height-BOARD_SPACE);
            if (ball.isSticky())
                if(width -FRAME_WIDTH-board.getWidth() > currentX+BOARD_SPEED)
                    ball.move(BOARD_SPEED, 0);
        }
        if ((keyStates & FIRE_PRESSED) != 0) {
            ball.setSticky(false);
        }
    }

    public void checkCollisions() {
        // See if the ball hit the board
        if(ball.collidesWith(board, false)) {
            // Calculate where on the board the ball hit
            int hit = ((ball.getX() + ball.getWidth()/2)
                       - board.getX()) - (board.getWidth()/2);
            int x = hit/3;
            int y = 5 - Math.abs(x);
            //XXX: Should be random
            if(x == 0) x++;
            if(y == 0) y--;
            ball.setAngle(x, y);
            if(y > 0) ball.reverseY();
            if (current_bonus == BonusBrick.STICKY_BONUS) {
                ball.setPosition(ball.getX(), board.getY() - ball.getHeight());
                ball.setSticky(true);
            }
        }

        // See if the ball hit any bricks
        if(bricks.checkCollisions(ball)) {
            // We have a collision, but where did we hit the brick?
            Brick brick = bricks.getBrick();
            int y_diff = brick.getHeight() - Math.abs(brick.getY() -ball.getY());
            // Divide by 2 since a brick is twice as wide as high
            int x_diff = (brick.getWidth() - Math.abs(brick.getX() - ball.getX())) / 2;
            if(current_bonus != BonusBrick.BREAK_BONUS) {
                if(y_diff < x_diff) ball.reverseY();
                else ball.reverseX();
            }
            points += 10;
            pointLayer.setNum(points);
            if (brick.getType() != 0) {
                bonus.addBonus(brick.getX(), brick.getY(), brick.getType());
            }
        }

        // See if the board picked up a bonus
        if(bonus.checkCollisions(board)) {
            switch(bonus.getType()) {
            case BonusBrick.NO_BONUS:
                break;
            case BonusBrick.POINT_BONUS:
                points += 100;
                pointLayer.setNum(points);
                break;
            case BonusBrick.STICKY_BONUS:
                current_bonus = BonusBrick.STICKY_BONUS;
                break;
            case BonusBrick.LIVE_BONUS:
                lives++;
                livesLayer.update(lives);
                break;
            case BonusBrick.BREAK_BONUS:
                current_bonus = BonusBrick.BREAK_BONUS;
                break;
            }
        }
    }

    public void render() {

        Graphics g = getGraphics();
        layerManager.paint(g, 0, 0);
        flushGraphics();
    }

    public synchronized void keyPressed(int keyCode) {
        layerManager.remove(textLayer);
        thread.resumeGame();
    }

}
