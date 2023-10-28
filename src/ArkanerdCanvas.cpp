#include "ArkanerdCanvas.h"
#include "BonusBrick.h"
#include "BonusLayer.h"
#include "BricksLayer.h"
#include "Main.h"

#include "j2me/GameCanvas.h"

namespace arkanerd {

ArkanerdCanvas::ArkanerdCanvas(Main *main, Settings *settings)
  : j2me::GameCanvas(main)
  , main_(main)
  , settings_(settings) {

  bgimage_ = j2me::Image::createImage("/levels/level" + std::to_string(level_num_ + 1) + ".png");
  int rows = (getHeight() / bgimage_.getHeight()) + 1;
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
  lives_layer_->setPosition(getWidth() - 20 - lives_layer_->getWidth(), 10);
  layer_manager_.append(board_.get());
  layer_manager_.append(ball_.get());
}

void ArkanerdCanvas::flushKeys() {
  getKeyStates();
}

void ArkanerdCanvas::dead() {
  if (lives_ == 0) {
    main_->gameOver(points_);
  }
  lives_--;
  lives_layer_->update(lives_);
  board_->setPosition(getWidth() / 2 - board_->getWidth() / 2, getHeight() - BOARD_SPACE);
  ball_->setPosition(getWidth() / 2 - ball_->getWidth() / 2, getHeight() - BOARD_SPACE - ball_->getHeight());
  bonus_layer_->reset();
  start();
}

void ArkanerdCanvas::start() {
  current_bonus_ = BonusBrick::NO_BONUS;

  text_layer_ = std::make_unique<TextLayer>(level_->getName(), getWidth() / TextLayer::WIDTH);
  text_layer_->setPosition((getWidth() - text_layer_->getWidth()) / 2, (getHeight() - text_layer_->getHeight()) / 2);
  layer_manager_.append(text_layer_.get());
  layer_manager_.clear();;
  paused_ = true;
}

void ArkanerdCanvas::nextLevel() {
  level_num_++;

  try {
    level_ = std::make_unique<Level>(level_num_);
  } catch (const std::runtime_error&) {
    main_->gameComplete(points_);
  }

  ball_->setAngle(2, -3);
  ball_->setPosition(getWidth() / 2 - ball_->getWidth() / 2, getHeight() - BOARD_SPACE - ball_->getHeight());

  board_->setPosition(getWidth() / 2 - board_->getWidth() / 2, getHeight() - BOARD_SPACE);

  layer_manager_.remove(bricks_layer_.get());
  bricks_layer_ = std::make_unique<BricksLayer>(this, level_.get());
  layer_manager_.append(bricks_layer_.get());

  if (bonus_layer_) {
    layer_manager_.remove(bonus_layer_.get());
  }
  bonus_layer_ = std::make_unique<BonusLayer>(this);
  layer_manager_.append(bonus_layer_.get());

  start();
}

void ArkanerdCanvas::update() {
  if (!paused_) {
    clear();
    input();
    checkCollisions();
    ball_->update();
    bonus_layer_->update();
    if (ball_->getY() > getHeight()) {
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
    board_->setPosition(std::max(FRAME_WIDTH, currentX - BOARD_SPEED), getHeight() - BOARD_SPACE);
    if (ball_->isSticky()) {
      if (currentX - BOARD_SPEED > FRAME_WIDTH) {
        ball_->move(-BOARD_SPEED, 0);
      }
    }
  }
  if ((keyStates & RIGHT_PRESSED) != 0) {
    board_->setPosition(std::min(getWidth() - FRAME_WIDTH - board_->getWidth(), currentX + BOARD_SPEED), getHeight() - BOARD_SPACE);
    if (ball_->isSticky()) {
      if (getWidth() - FRAME_WIDTH - board_->getWidth() > currentX + BOARD_SPEED) {
        ball_->move(BOARD_SPEED, 0);
     }
    }
  }
  if ((keyStates & FIRE_PRESSED) != 0) {
    ball_->setSticky(false);
  }
}

void ArkanerdCanvas::checkCollisions() {
  if (ball_->collidesWith(board_.get(), false)) {
    int hit = ((ball_->getX() + ball_->getWidth() / 2) - board_->getX()) - (board_->getWidth() / 2);
    int x = hit / 3;
    int y = 5 - std::abs(x);
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

  if (bricks_layer_->checkCollisions(ball_.get())) {
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
      bonus_layer_->addBonus(brick.getX(), brick.getY(), brick.getType());
    }
  }

  if (bonus_layer_->checkCollisions(board_.get())) {
    switch (bonus_layer_->getType()) {
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
  layer_manager_.remove(text_layer_.get());
  paused_ = false;
  j2me::GameCanvas::keyPressed(keyCode);
}

} // namespace arkanerd

