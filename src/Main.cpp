#include "Main.h"

#include "j2me/Display.h"
#include "j2me/StringItem.h"
#include "j2me/ImageItem.h"

namespace arkanerd {

Main::Main()
  : display_(j2me::Display::getDisplay(this)) {
  settings_ = new Settings();
}

void Main::startApp() {
  titleCanvas_ = new TitleCanvas(this);
  display_->setCurrent(titleCanvas_);
}

void Main::destroyApp(bool /*unconditional*/) {
}

void Main::commandAction(const j2me::Command& cmd, const j2me::Displayable& /*dsp*/) {
  if (cmd.getCommandType() == j2me::Command::EXIT) {
    destroyApp(true);
    notifyDestroyed();
  } else if (cmd.getCommandType() == j2me::Command::BACK) {
    showMenu();
  } else if (cmd == SAVE_COMMAND) {
    std::vector<bool> selected(settings_menu->size());
    // Fill array indicating whether each element is checked
    settings_menu->getSelectedFlags(selected);
    settings_->setMusic(selected[0]);
    showMenu();
  } else {
    j2me::List* menu = static_cast<j2me::List*>(display_->getCurrent());
    switch (menu->getSelectedIndex()) {
			case 0:
				newGame();
				break;
			case 1:
				instructions();
				break;
			case 2:
				highScores();
				break;
			case 3:
				settings();
				break;
			case 4:
				about();
				break;
			}
		}
	}

void Main::showMenu() {
  std::vector<std::string> menuItems = {"New game", "Instructions", "High Scores", "Settings", "About"};
  j2me::List *menu = new j2me::List(this, "Arkanerd", j2me::Choice::IMPLICIT, menuItems, {});
  menu->addCommand(EXIT_COMMAND);
  menu->setCommandListener(this);
  display_->setCurrent(menu);
}

void Main::gameComplete(int points) {
  j2me::Form *gameCompleteForm = new j2me::Form(this, "Game completed!");
  auto gameOverString = std::make_unique<j2me::StringItem>(std::nullopt, "You did it!\n");
  gameOverString->setFont(j2me::Font::getFont(j2me::Font::FACE_MONOSPACE, j2me::Font::STYLE_BOLD, j2me::Font::SIZE_LARGE));
  auto s1 = std::make_unique<j2me::StringItem>(std::nullopt, "You completed all leves!");
  auto s2 = std::make_unique<j2me::StringItem>(std::nullopt, "Please go to http://www.linuxfan.dk");
  auto s3 = std::make_unique<j2me::StringItem>(std::nullopt, "To look for more levels");
  gameOverString->setLayout(j2me::Item::LAYOUT_CENTER);
  s1->setLayout(j2me::Item::LAYOUT_CENTER);
  s2->setLayout(j2me::Item::LAYOUT_CENTER);
  s3->setLayout(j2me::Item::LAYOUT_CENTER);
  gameCompleteForm->append(std::move(gameOverString));
  gameCompleteForm->append(std::move(s1));
  gameCompleteForm->append(std::move(s2));
  gameCompleteForm->append(std::move(s3));
  showScoreString(points, gameCompleteForm);
  gameCompleteForm->addCommand(BACK_COMMAND);
  gameCompleteForm->setCommandListener(this);
  display_->setCurrent(gameCompleteForm);
}

void Main::gameOver(int points) {
  j2me::Form* gameOverForm = new j2me::Form(this, "Game over!");
  auto deadString = std::make_unique<j2me::StringItem>(std::nullopt, "Game over!\n");
  deadString->setFont(j2me::Font::getFont(j2me::Font::FACE_MONOSPACE, j2me::Font::STYLE_BOLD, j2me::Font::SIZE_LARGE));
  deadString->setLayout(j2me::Item::LAYOUT_CENTER);
  gameOverForm->append(std::move(deadString));
  showScoreString(points, gameOverForm);
  gameOverForm->addCommand(BACK_COMMAND);
  gameOverForm->setCommandListener(this);
  display_->setCurrent(gameOverForm);
}

void Main::newGame() {
  arkanerd_canvas_ = new ArkanerdCanvas(this, settings_);
  arkanerd_canvas_->nextLevel();
  display_->setCurrent(arkanerd_canvas_);
}

void Main::showScoreString(int score, j2me::Form* form) {
  if (score > settings_->getHighScore()) {
    settings_->setHighScore(score);
    auto s1 = std::make_unique<j2me::StringItem>(std::nullopt, "Congratulations!\n");
    auto s2 = std::make_unique<j2me::StringItem>(std::nullopt, "You got a new High Score:\n");
    auto s3 = std::make_unique<j2me::StringItem>(std::nullopt, std::to_string(score));
    s1->setLayout(j2me::Item::LAYOUT_CENTER);
    s2->setLayout(j2me::Item::LAYOUT_CENTER);
    s3->setLayout(j2me::Item::LAYOUT_CENTER);
    form->append(std::move(s1));
    form->append(std::move(s2));
    form->append(std::move(s3));
  } else {
    auto s1 = std::make_unique<j2me::StringItem>(std::nullopt, "Your Score:\n");
    auto s2 = std::make_unique<j2me::StringItem>(std::nullopt, std::to_string(score) + "\n");
    auto s3 = std::make_unique<j2me::StringItem>(std::nullopt, "High Score:\n");
    auto s4 = std::make_unique<j2me::StringItem>(std::nullopt, std::to_string(settings_->getHighScore()));
    s1->setLayout(j2me::Item::LAYOUT_CENTER);
    s2->setLayout(j2me::Item::LAYOUT_CENTER);
    s3->setLayout(j2me::Item::LAYOUT_CENTER);
    s4->setLayout(j2me::Item::LAYOUT_CENTER);
    form->append(std::move(s1));
    form->append(std::move(s2));
    form->append(std::move(s3));
    form->append(std::move(s4));
  }
}

void Main::settings() {
  settings_menu = new j2me::List(this, "Settings", j2me::List::MULTIPLE);
  settings_menu->append("Enable Music", {});
  settings_menu->setSelectedIndex(0, settings_->musicOn());
  settings_menu->setCommandListener(this);
  settings_menu->addCommand(BACK_COMMAND);
  settings_menu->addCommand(SAVE_COMMAND);
  settings_menu->setCommandListener(this);
  display_->setCurrent(settings_menu);
}

void Main::highScores() {
  j2me::Form *highScoreForm = new j2me::Form(this, "High Score");
  auto highString = std::make_unique<j2me::StringItem>(std::nullopt, "High score: " + std::to_string(settings_->getHighScore()));
  highString->setLayout(j2me::Item::LAYOUT_CENTER);
  highScoreForm->append(std::move(highString));
  highScoreForm->addCommand(BACK_COMMAND);
  highScoreForm->setCommandListener(this);
  display_->setCurrent(highScoreForm);
}

void Main::instructions() {
  j2me::Form *instructionsForm = new j2me::Form(this, "Instructions");
  instructionsForm->append("Arkanerd is a little Arkanoid/Break-out like game.\n\n"
                           "The goal of the game is to clear out the colored bricks "
                           "placed in the central part of the screen\n\n"
                           "This is achieved by bouncing the ball around the screen, which "
                           "is done by moving the small platform located at the bottom of "
                           "the screen.\n\n"
                           "Be careful though, since you have to catch the ball before it "
                           "leaves the screen, otherwise you lose a life.\n\n"
                           "Special bricks releases a special bonus when you hit them, which, "
                           "when \"picked up\" with the player-controlled platform, changes the "
                           "gameplay in different ways.\n\n"
                           "The special powerup bonuses are:\n");
  j2me::Image img = j2me::Image::createImage(j2me::Image::createImage("/images/bonus1.png"), 0, 0, 20, 10, j2me::Sprite::TRANS_NONE);
  auto bonus = std::make_unique<j2me::ImageItem>("100 Points", img, j2me::Item::LAYOUT_LEFT | j2me::Item::LAYOUT_NEWLINE_AFTER, "");
  instructionsForm->append(std::move(bonus));
  instructionsForm->append("Adds 100 points to the current score.");

  img = j2me::Image::createImage(j2me::Image::createImage("/images/bonus2.png"), 0, 0, 20, 10, j2me::Sprite::TRANS_NONE);
  bonus = std::make_unique<j2me::ImageItem>("Sticky ball", img, j2me::Item::LAYOUT_LEFT | j2me::Item::LAYOUT_NEWLINE_AFTER, "");
  instructionsForm->append(std::move(bonus));
  instructionsForm->append("The ball \"sticks\" to the platform. Press the \"fire\" button to release it.");

  img = j2me::Image::createImage(j2me::Image::createImage("/images/bonus3.png"), 0, 0, 20, 10, j2me::Sprite::TRANS_NONE);
  bonus = std::make_unique<j2me::ImageItem>("Power ball", img, j2me::Item::LAYOUT_LEFT | j2me::Item::LAYOUT_NEWLINE_AFTER, "");
  instructionsForm->append(std::move(bonus));
  instructionsForm->append("The ball doesn't bounce off the bricks, instead it shoots right through them.");

  img = j2me::Image::createImage(j2me::Image::createImage("/images/bonus4.png"), 0, 0, 20, 10, j2me::Sprite::TRANS_NONE);
  bonus = std::make_unique< j2me::ImageItem>("Extra life", img, j2me::Item::LAYOUT_LEFT | j2me::Item::LAYOUT_NEWLINE_AFTER, "");
  instructionsForm->append(std::move(bonus));
  instructionsForm->append("Gives you an extra life.\n");
  instructionsForm->append("\n");
  instructionsForm->append("\nEnjoy your time with Arkanerd!");

  instructionsForm->addCommand(BACK_COMMAND);
  instructionsForm->setCommandListener(this);
  display_->setCurrent(instructionsForm);
}

void Main::about() {
  j2me::Form* aboutForm = new j2me::Form(this, "About Arkanerd");
  std::string aboutText = "A little Arkanoid/Break-out like game for Java MIDP 2.0\n\n"
    "Copyright (C) 2006 Kasper Laudrup\n\n"
    "Arkanerd is free software, covered by the GNU General Public License,"
    " and you are welcome to change it and/or distribute copies of it"
    " under certain conditions.\n\n"
    "Please see http://www.linuxfan.dk for source code etc.";
  auto tempVar = std::make_unique<j2me::StringItem>(std::nullopt, aboutText);
  aboutForm->append(std::move(tempVar));
  aboutForm->addCommand(BACK_COMMAND);
  aboutForm->setCommandListener(this);
  display_->setCurrent(aboutForm);
}

} // namespace arkanerd

int main() {
  arkanerd::Main main;
  main.run();
}
