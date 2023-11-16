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
  inline static constexpr int UP_PRESSED = 0x0002;
  inline static constexpr int DOWN_PRESSED = 0x0040;
  inline static constexpr int LEFT_PRESSED = 0x0004;
  inline static constexpr int RIGHT_PRESSED = 0x0020;
  inline static constexpr int FIRE_PRESSED = 0x0100;
  inline static constexpr int GAME_A_PRESSED =  0x0200;
  inline static constexpr int GAME_B_PRESSED =  0x0400;
  inline static constexpr int GAME_C_PRESSED =  0x0800;
  inline static constexpr int GAME_D_PRESSED = 0x1000;

  ArkanerdCanvas(Main* main, Settings* settings);
  int getKeyStates();
  j2me::Graphics* getGraphics();
  void flushGraphics();
  void paint(j2me::Graphics* g);
  void keyPressed(sf::Keyboard::Key keyCode);
  void flushKeys();
  bool dead();
  bool nextLevel();
  void update();
  void input();
  void checkCollisions();
  void render();
  void clear();

private:
  friend class BonusLayer;
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
  const int BOARD_SPEED = 5;
};

} // namespace arkanerd

