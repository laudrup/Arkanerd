#pragma once

#include "Settings.h"

#include "j2me/Command.h"
#include "j2me/CommandListener.h"
#include "j2me/Display.h"
#include "j2me/Displayable.h"
#include "j2me/MIDlet.h"

#include <string>
#include <vector>

namespace arkanerd {

class Main : public j2me::MIDlet, j2me::CommandListener {

public:
  inline static const j2me::Command BACK_COMMAND{"Back", j2me::Command::BACK, 0};
  inline static const j2me::Command EXIT_COMMAND{"Exit", j2me::Command::EXIT, 1};
  inline static const j2me::Command SAVE_COMMAND{"Save", j2me::Command::SCREEN, 2};

  Main();
  void showMenu();
  void gameComplete(int points);
  void gameOver(int points);

private:
  void commandAction(const j2me::Command& cmd, const j2me::Displayable& dsp) final;
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

