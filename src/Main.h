#pragma once

#include "TitleCanvas.h"
#include "Settings.h"
#include "ArkanerdCanvas.h"
#include "ArkanerdThread.h"

#include "j2me/Command.h"
#include "j2me/CommandListener.h"
#include "j2me/Display.h"
#include "j2me/Displayable.h"
#include "j2me/Form.h"
#include "j2me/List.h"
#include "j2me/MIDlet.h"

#include <string>
#include <vector>

/*
  Main.java

  Arkanerd - An Arkanoid/Breakout like game for J2ME mobile phones
  Copyright (C) 2006  Kasper Laudrup

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

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
  void startApp() final;
  void destroyApp(bool unconditional) final;
  void commandAction(const j2me::Command& cmd, const j2me::Displayable& dsp) final;
  void newGame();
  void showScoreString(int score, j2me::Form* form);
  void settings();
  void highScores();
  void instructions();
  void about();

  j2me::Display* display_;
  TitleCanvas* titleCanvas_;
  Settings* settings_;
  ArkanerdCanvas* arkanerd_canvas_;
  ArkanerdThread* arkanerd_thread_;
  j2me::List* settings_menu;
};

} // namespace arkanerd

