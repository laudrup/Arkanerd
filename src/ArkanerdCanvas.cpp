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
  board_ = std::make_unique<Board>();
  ball_ = std::make_unique<Ball>(this);

  point_layer_ = std::make_unique<PointLayer>(5);
  point_layer_->setPosition(20,10);

  lives_layer_ = std::make_unique<LivesLayer>(lives_);
  lives_layer_->setPosition(getWidth() - 20 - lives_layer_->getWidth(), 10);
}

void ArkanerdCanvas::flushKeys() {
  getKeyStates();
}

bool ArkanerdCanvas::dead() {
  if (lives_ == 0) {
    main_->gameOver(points_);
    return false;
  }
  lives_--;
  lives_layer_->update(lives_);

  board_->setPosition(getWidth() / 2 - board_->getWidth() / 2, getHeight() - BOARD_SPACE);
  ball_->setPosition(getWidth() / 2 - ball_->getWidth() / 2, getHeight() - BOARD_SPACE - ball_->getHeight());

  start();
  return true;
}

void ArkanerdCanvas::start() {
  current_bonus_ = BonusBrick::NO_BONUS;

  text_layer_ = std::make_unique<TextLayer>(level_->getName(), getWidth() / TextLayer::WIDTH);
  text_layer_->setPosition((getWidth() - text_layer_->getWidth()) / 2, (getHeight() - text_layer_->getHeight()) / 2);
  paused_ = true;
}

bool ArkanerdCanvas::nextLevel() {
  level_num_++;

  try {
    level_ = std::make_unique<Level>(level_num_);
  } catch (const std::runtime_error&) {
    main_->gameComplete(points_);
    return false;
  }

  auto bgimage = j2me::Image::createImage("/levels/level" + std::to_string(level_num_) + ".png");
  int rows = (getHeight() / bgimage.getHeight()) + 1;
  bg_layer_ = std::make_unique<j2me::TiledLayer>(1, rows, bgimage, bgimage.getWidth(), bgimage.getHeight());
  bg_layer_->fillCells(0,0,1,rows,1);

  ball_->setAngle(2, -3);

  board_->setPosition(getWidth() / 2 - board_->getWidth() / 2, getHeight() - BOARD_SPACE);
  ball_->setPosition(getWidth() / 2 - ball_->getWidth() / 2, getHeight() - BOARD_SPACE - ball_->getHeight());

  bricks_layer_ = std::make_unique<BricksLayer>(this, level_.get());
  bonus_layer_ = std::make_unique<BonusLayer>(this);
  start();
  return true;
}

void ArkanerdCanvas::update() {
  if (!paused_) {
    clear();
    input();
    checkCollisions();
    ball_->update();
    bonus_layer_->update();
    if (ball_->getY() > getHeight()) {
      if (!dead()) {
        return;
      }
      // GOD MODE:
      //ball_->reverseY();
    }
    if (bricks_layer_->getBricksLeft() == 0) {
      if (!nextLevel()) {
        return;
      }
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
  point_layer_->clear();
  lives_layer_->clear();
}

void ArkanerdCanvas::render() {
  j2me::Graphics* g = getGraphics();
  bg_layer_->paint(g);
  point_layer_->paint(g);
  lives_layer_->paint(g);
  bricks_layer_->paint(g);
  board_->paint(g);
  ball_->paint(g);
  bonus_layer_->paint(g);
  if (paused_) {
    text_layer_->clear();
    text_layer_->paint(g);
  }
}

void ArkanerdCanvas::keyPressed(int keyCode) {
  paused_ = false;
  j2me::GameCanvas::keyPressed(keyCode);
}

} // namespace arkanerd

