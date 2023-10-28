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

#include "j2me/GameCanvas.h"
#include "j2me/Image.h"
#include "j2me/Player.h"
#include "j2me/TiledLayer.h"
#include "j2me/LayerManager.h"

#include <cmath>
#include <stdexcept>
#include <mutex>

namespace arkanerd {
class Main;

class ArkanerdCanvas : public j2me::GameCanvas {
public:
  static constexpr int FRAME_WIDTH = 7;
  static constexpr int FRAME_TOP = 40; // Vi skal have denne fra et eller andet sted
  static constexpr int BOARD_SPACE = 20;

  ArkanerdCanvas(Main* main, Settings* settings);
  void flushKeys();
  void dead();
  void nextLevel();
  void update() override;
  void input();
  void checkCollisions();
  void render();
  void clear();
  void keyPressed(int keyCode) override;

private:
  friend class BricksLayer;
  void start();

  Main* main_ = nullptr;
  Settings* settings_ = nullptr;
  bool paused_ = true;

  j2me::LayerManager layer_manager_;

  std::unique_ptr<j2me::TiledLayer> bg_layer_;
  std::unique_ptr<Board> board_;
  std::unique_ptr<Ball> ball_;
  std::unique_ptr<BonusLayer> bonus_layer_;
  std::unique_ptr<BricksLayer> bricks_layer_;
  std::unique_ptr<j2me::Player> player_;
  std::unique_ptr<PointLayer> point_layer_;
  std::unique_ptr<LivesLayer> lives_layer_;
  std::unique_ptr<TextLayer> text_layer_;
  std::unique_ptr<Level> level_;
  int current_bonus_ = 0;
  int lives_ = 3;
  int points_ = 0;
  int level_num_ = 0;
  const int BOARD_SPEED = 5;
};

} // namespace arkanerd

