#pragma once

#include "Canvas.h"

namespace j2me {

class GameCanvas : public Canvas {
public:
  virtual ~GameCanvas() = default;
  int getKeyStates();
  void flushGraphics();
  void paint(Graphics* g) override;
  virtual void update() = 0;
  void keyPressed(int keyCode) override;

  inline static constexpr int UP_PRESSED = 0x0002;
  inline static constexpr int DOWN_PRESSED = 0x0040;
  inline static constexpr int LEFT_PRESSED = 0x0004;
  inline static constexpr int RIGHT_PRESSED = 0x0020;
  inline static constexpr int FIRE_PRESSED = 0x0100;
  inline static constexpr int GAME_A_PRESSED =  0x0200;
  inline static constexpr int GAME_B_PRESSED =  0x0400;
  inline static constexpr int GAME_C_PRESSED =  0x0800;
  inline static constexpr int GAME_D_PRESSED = 0x1000;

protected:
  using Canvas::Canvas;
  Graphics* getGraphics();
  Graphics* graphics_ = nullptr;

  int key_states_ = 0;
};

} // namespace j2me
