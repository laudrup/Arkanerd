#pragma once

#include "Board.h"
#include "Ball.h"
#include "Bonus.h"
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
class BricksLayer;

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

  bool paused_ = true;
  Board* board_ = nullptr;
  //private Font f;
  Main* main_ = nullptr;
  Ball* ball_ = nullptr;
  Bonus* bonus_ = nullptr;
  BricksLayer* bricks_layer_ = nullptr;
  j2me::Image bgimage_;
  j2me::Player* player_ = nullptr;
  //private boolean music_on;
  Settings* settings_ = nullptr;
  PointLayer* point_layer_ = nullptr;
  LivesLayer* lives_layer_ = nullptr;
  j2me::TiledLayer* bg_layer_ = nullptr;
  TextLayer* textLayer;
  j2me::LayerManager* layer_manager_ = nullptr;
  Level* level_;
  int current_bonus_ = 0;
  int width_ = 0;
  int height_ = 0;
  int lives_ = 0;
  int points_ = 0;
  int level_num_ = 0;
  const int BOARD_SPEED = 5;
};

} // namespace arkanerd

