#pragma once

#include "Board.h"
#include "Ball.h"
#include "BonusLayer.h"
#include "BricksLayer.h"
#include "Settings.h"
#include "PointLayer.h"
#include "LivesLayer.h"
#include "TextLayer.h"
#include "Level.h"

#include "j2me/Canvas.h"
#include "j2me/TiledLayer.h"

namespace arkanerd {
class Main;

class ArkanerdCanvas : public j2me::Canvas {
public:
  inline static constexpr int FRAME_WIDTH = 7;
  inline static constexpr int FRAME_TOP = 40; // Vi skal have denne fra et eller andet sted
  inline static constexpr int BOARD_SPACE = 20;

  ArkanerdCanvas(Main* main, Settings* settings);
  int getKeyStates();
  j2me::Graphics* getGraphics();
  void paint(j2me::Graphics* g);
  void update();
  bool nextLevel();
  void keyPressed(sf::Keyboard::Key keyCode);

private:
  friend class BonusLayer;

  bool dead();
  void input();
  void checkCollisions();
  void render();
  void clear();
  void start();

  Main* main_ = nullptr;
  Settings* settings_ = nullptr;
  j2me::Graphics* graphics_ = nullptr;
  bool paused_ = true;

  std::unique_ptr<j2me::TiledLayer> bg_layer_;
  std::unique_ptr<Board> board_;
  std::unique_ptr<Ball> ball_;
  std::unique_ptr<BonusLayer> bonus_layer_;
  std::unique_ptr<BricksLayer> bricks_layer_;
  std::unique_ptr<PointLayer> point_layer_;
  std::unique_ptr<LivesLayer> lives_layer_;
  std::unique_ptr<TextLayer> text_layer_;
  std::unique_ptr<Level> level_;
  int current_bonus_ = 0;
  int lives_ = 3;
  int points_ = 0;
  int level_num_ = 0;
  int key_states_ = 0;
};

} // namespace arkanerd

