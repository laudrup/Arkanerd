#pragma once

#include "Settings.h"

#include "j2me/CommandListener.h"
#include "j2me/Display.h"
#include "j2me/MIDlet.h"

#include <string>
#include <vector>

namespace arkanerd {

class Main : public j2me::MIDlet, j2me::CommandListener {

public:
  Main();
  void showMenu();
  void gameComplete(int points);
  void gameOver(int points);

private:
  void newGame();
  std::string getScoreString(int score);
  void settings();
  void highScores();
  void instructions();
  void about();

  j2me::Display* display_;
  std::unique_ptr<Settings> settings_;
};

} // namespace arkanerd

