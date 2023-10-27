#include "ArkanerdCanvas.h"
#include "BonusBrick.h"
#include "BricksLayer.h"
#include "Main.h"
#include "j2me/GameCanvas.h"
#include <iostream>
#include <thread>

namespace arkanerd {

ArkanerdCanvas::ArkanerdCanvas(Main *main, Settings *settings)
  : j2me::GameCanvas(main) {
  //XXX: This slows down the game generates keyevents
  setFullScreenMode(true);
  this->main_ = main;
  this->settings_ = settings;
  //setCommandListener(main);
  width_ = getWidth();
  height_ = getHeight(); // - FRAME_TOP;
  level_num_ = 1;
  lives_ = 3;
  //layer_manager_ = new j2me::LayerManager();
  //f = Font.getFont(Font.FACE_MONOSPACE, Font.STYLE_BOLD, Font.SIZE_SMALL);

  bgimage_ = j2me::Image::createImage("/levels/level" + std::to_string(level_num_) + ".png");
  int rows = (height_ / bgimage_.getHeight()) + 1;
  if (bg_layer_) {
    layer_manager_.remove(bg_layer_.get());
  }
  bg_layer_ = std::make_unique<j2me::TiledLayer>(1, rows, bgimage_, bgimage_.getWidth(), bgimage_.getHeight());
  bg_layer_->fillCells(0,0,1,rows,1);
  layer_manager_.append(bg_layer_.get());

  board_ = std::make_unique<Board>();
  ball_ = std::make_unique<Ball>(this);
  point_layer_ = std::make_unique<PointLayer>(5);
  lives_layer_ = std::make_unique<LivesLayer>(lives_);

  layer_manager_.append(point_layer_.get());
  layer_manager_.append(lives_layer_.get());
  point_layer_->setPosition(20,10);
  lives_layer_->setPosition(width_ - 20 - lives_layer_->getWidth(), 10);
  layer_manager_.append(board_.get());
  layer_manager_.append(ball_.get());
}

void ArkanerdCanvas::flushKeys() {
  getKeyStates();
}

void ArkanerdCanvas::dead() {
  //XXX Vibrate doesn't work??
  //Display display = Display.getDisplay(main);
  //display.vibrate(1000);
  if (lives_ == 0) {
    main_->gameOver(points_);
  }
  lives_--;
  lives_layer_->update(lives_);
  board_->setPosition(width_ / 2 - board_->getWidth() / 2, height_ - BOARD_SPACE);
  ball_->setPosition(width_ / 2 - ball_->getWidth() / 2, height_ - BOARD_SPACE - ball_->getHeight());
  bonus_->clear();
  // Show start text and pause game
  start();
}

void ArkanerdCanvas::start() {
  current_bonus_ = BonusBrick::NO_BONUS;

  //Show the level name
  textLayer = std::make_unique<TextLayer>(level_->getName(), width_ / TextLayer::WIDTH);
  textLayer->setPosition((width_ - textLayer->getWidth()) / 2, (height_ - textLayer->getHeight()) / 2);
  layer_manager_.append(textLayer.get());
  /*
  if (player_) {
    if (player_->getState() != j2me::Player::STARTED) {
      player_->start();
    }
  }
  */
  paused_ = true;
}

void ArkanerdCanvas::nextLevel() {
  level_num_++;
  // Try and load the new level if unsuccesfull, no more levels available
  try {
    level_ = std::make_unique<Level>(level_num_);
  } catch (const std::runtime_error& ex) {
    std::cerr << "Whoops: " << ex.what() << "\n";
    main_->gameComplete(points_);
  }
  if (bonus_ != nullptr) {
    bonus_->clear();
  }
  bonus_ = std::make_unique<Bonus>(&layer_manager_, this);

  //TODO:
  ball_->setAngle(2, -3);
  ball_->setPosition(width_ / 2 - ball_->getWidth() / 2, height_ - BOARD_SPACE - ball_->getHeight());

  // Set up the new bricks for this level
  board_->setPosition(width_ / 2 - board_->getWidth() / 2, height_ - BOARD_SPACE);
  layer_manager_.remove(bricks_layer_.get());
  bricks_layer_ = std::make_unique<BricksLayer>(this, level_.get());
  layer_manager_.append(bricks_layer_.get());

		// Set music for this level (if possible)
  if (settings_->musicOn()) {
    if (player_  && player_->getState() == j2me::Player::STARTED) {
      player_->close();
    }
    //InputStream *ins = getClass().getResourceAsStream("/levels/level" + std::to_string(level_num) + ".mid");
    //player_ = Manager::createPlayer(ins, "audio/midi");
    //player_->setLoopCount(-1);
  }

  // Render the initial graphics
  //render();

  // Show start text and pause game
  start();
}

void ArkanerdCanvas::update() {
  if (!paused_) {
    clear();
    input();
    checkCollisions();
    ball_->update();
    bonus_->update();
    if (ball_->getY() > height_) {
      dead();
      // GOD MODE:
      //ball_->reverseY();
    }
    if (bricks_layer_->getBricksLeft() == 0) {
      nextLevel();
    }
  }
  render();
}

void ArkanerdCanvas::input() {
  int keyStates = getKeyStates();
  int currentX = board_->getX();
  if ((keyStates & LEFT_PRESSED) != 0) {
    board_->setPosition(std::max(FRAME_WIDTH, currentX - BOARD_SPEED), height_ - BOARD_SPACE);
    if (ball_->isSticky()) {
      if (currentX - BOARD_SPEED > FRAME_WIDTH) {
        ball_->move(-BOARD_SPEED, 0);
      }
    }
  }
  if ((keyStates & RIGHT_PRESSED) != 0) {
    board_->setPosition(std::min(width_ - FRAME_WIDTH - board_->getWidth(), currentX + BOARD_SPEED), height_ - BOARD_SPACE);
    if (ball_->isSticky()) {
      if (width_ - FRAME_WIDTH - board_->getWidth() > currentX + BOARD_SPEED) {
        ball_->move(BOARD_SPEED, 0);
     }
    }
  }
  if ((keyStates & FIRE_PRESSED) != 0) {
    ball_->setSticky(false);
  }
}

void ArkanerdCanvas::checkCollisions() {
  // See if the ball hit the board
  if (ball_->collidesWith(board_.get(), false)) {
    // Calculate where on the board the ball hit
    int hit = ((ball_->getX() + ball_->getWidth() / 2) - board_->getX()) - (board_->getWidth() / 2);
    int x = hit / 3;
    int y = 5 - std::abs(x);
    //XXX: Should be random
    if (x == 0) {
      x++;
    }
    if (y == 0) {
      y--;
    }
    ball_->setAngle(x, y);
    if (y > 0) {
      ball_->reverseY();
    }
    if (current_bonus_ == BonusBrick::STICKY_BONUS) {
      ball_->setPosition(ball_->getX(), board_->getY() - ball_->getHeight());
      ball_->setSticky(true);
    }
  }

  // See if the ball hit any bricks
  if (bricks_layer_->checkCollisions(ball_.get())) {
    // We have a collision, but where did we hit the brick?
    auto brick = bricks_layer_->getBrick();
    sf::Rect brick_bounds{brick.getX(), brick.getY(), brick.getWidth(), brick.getHeight()};
    sf::Rect ball_bounds{ball_->getX(), ball_->getY(), ball_->getWidth(), ball_->getHeight()};
    sf::Rect<int> intersection;
    brick_bounds.intersects(ball_bounds, intersection);
    if (intersection.width > intersection.height) {
      ball_->reverseY();
    } else {
      ball_->reverseX();
    }
    points_ += 10;
    point_layer_->setNum(points_);
    if (brick.getType() != 0) {
      bonus_->addBonus(brick.getX(), brick.getY(), brick.getType());
    }
  }

  // See if the board picked up a bonus
  if (bonus_->checkCollisions(board_.get())) {
    switch (bonus_->getType()) {
      case BonusBrick::NO_BONUS:
        break;
      case BonusBrick::POINT_BONUS:
        points_ += 100;
        point_layer_->setNum(points_);
        break;
      case BonusBrick::STICKY_BONUS:
        current_bonus_ = BonusBrick::STICKY_BONUS;
        break;
      case BonusBrick::LIVE_BONUS:
        lives_++;
        lives_layer_->update(lives_);
        break;
      case BonusBrick::BREAK_BONUS:
        current_bonus_ = BonusBrick::BREAK_BONUS;
        break;
    }
  }
}

void ArkanerdCanvas::clear() {
  layer_manager_.clear();;
}

void ArkanerdCanvas::render() {
  j2me::Graphics* g = getGraphics();
  layer_manager_.paint(g, 0, 0);
}

void ArkanerdCanvas::keyPressed(int keyCode) {
  layer_manager_.remove(textLayer.get());
  paused_ = false;
  j2me::GameCanvas::keyPressed(keyCode);
}

} // namespace arkanerd

