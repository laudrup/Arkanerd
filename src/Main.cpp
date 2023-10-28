#include "Main.h"
#include "ArkanerdCanvas.h"
#include "TitleCanvas.h"

#include "j2me/Display.h"
#include "j2me/StringItem.h"
#include "j2me/ImageItem.h"
#include "j2me/List.h"

#include <cassert>

namespace arkanerd {

Main::Main()
  : display_(j2me::Display::getDisplay(this))
  , settings_(std::make_unique<Settings>()) {

  auto title = std::make_unique<TitleCanvas>(this, [this]() {
    showMenu();
  });
  display_->setCurrent(std::move(title));
}

void Main::commandAction(const j2me::Command& cmd, const j2me::Displayable& /*dsp*/) {
  if (cmd.getCommandType() == j2me::Command::BACK) {
    showMenu();
  } else if (cmd == SAVE_COMMAND) {
    auto settings_menu = dynamic_cast<j2me::List*>(display_->getCurrent());
    assert(settings_menu != nullptr);
    std::vector<bool> selected(settings_menu->size());
    // Fill array indicating whether each element is checked
    settings_menu->getSelectedFlags(selected);
    settings_->setMusic(selected[0]);
    showMenu();
  } else {
    const j2me::List* menu = static_cast<j2me::List*>(display_->getCurrent());
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
  auto menu = std::make_unique<j2me::List>(this, "Arkanerd", j2me::Choice::IMPLICIT, menuItems, std::vector<j2me::Image>{});
  menu->addCommand(EXIT_COMMAND);
  menu->setCommandListener(this);
  display_->setCurrent(std::move(menu));
}

void Main::gameComplete(int points) {
  auto form = std::make_unique<j2me::Form>(this, "Game completed!");
  auto gameOverString = std::make_unique<j2me::StringItem>(std::nullopt, "You did it!\n");
  gameOverString->setFont(j2me::Font::getFont(j2me::Font::FACE_MONOSPACE, j2me::Font::STYLE_BOLD, j2me::Font::SIZE_LARGE));
  auto s1 = std::make_unique<j2me::StringItem>(std::nullopt, "You completed all leves!");
  auto s2 = std::make_unique<j2me::StringItem>(std::nullopt, "Please go to http://www.linuxfan.dk");
  auto s3 = std::make_unique<j2me::StringItem>(std::nullopt, "To look for more levels");
  gameOverString->setLayout(j2me::Item::LAYOUT_CENTER);
  s1->setLayout(j2me::Item::LAYOUT_CENTER);
  s2->setLayout(j2me::Item::LAYOUT_CENTER);
  s3->setLayout(j2me::Item::LAYOUT_CENTER);
  form->append(std::move(gameOverString));
  form->append(std::move(s1));
  form->append(std::move(s2));
  form->append(std::move(s3));
  showScoreString(points, form.get());
  form->addCommand(BACK_COMMAND);
  form->setCommandListener(this);
  display_->setCurrent(std::move(form));
}

void Main::gameOver(int points) {
  auto form = std::make_unique<j2me::Form>(this, "Game over!");
  auto deadString = std::make_unique<j2me::StringItem>(std::nullopt, "Game over!\n");
  deadString->setFont(j2me::Font::getFont(j2me::Font::FACE_MONOSPACE, j2me::Font::STYLE_BOLD, j2me::Font::SIZE_LARGE));
  deadString->setLayout(j2me::Item::LAYOUT_CENTER);
  form->append(std::move(deadString));
  showScoreString(points, form.get());
  form->addCommand(BACK_COMMAND);
  form->setCommandListener(this);
  display_->setCurrent(std::move(form));
}

void Main::newGame() {
  auto canvas = std::make_unique<ArkanerdCanvas>(this, settings_.get());
  display_->setCurrent(std::move(canvas));
  dynamic_cast<ArkanerdCanvas*>(display_->getCurrent())->nextLevel();
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
  auto menu = std::make_unique<j2me::List>(this, "Settings", j2me::List::MULTIPLE);
  menu->append("Enable Music", {});
  menu->setSelectedIndex(0, settings_->musicOn());
  menu->setCommandListener(this);
  menu->addCommand(BACK_COMMAND);
  menu->addCommand(SAVE_COMMAND);
  menu->setCommandListener(this);
  display_->setCurrent(std::move(menu));
}

void Main::highScores() {
  auto form = std::make_unique<j2me::Form>(this, "High Score");
  auto highString = std::make_unique<j2me::StringItem>(std::nullopt, "High score: " + std::to_string(settings_->getHighScore()));
  highString->setLayout(j2me::Item::LAYOUT_CENTER);
  form->append(std::move(highString));
  form->addCommand(BACK_COMMAND);
  form->setCommandListener(this);
  display_->setCurrent(std::move(form));
}

void Main::instructions() {
  auto form = std::make_unique<j2me::Form>(this, "Instructions");
  form->append("Arkanerd is a little Arkanoid/Break-out like game.\n\n"
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
  form->append(std::move(bonus));
  form->append("Adds 100 points to the current score.");

  img = j2me::Image::createImage(j2me::Image::createImage("/images/bonus2.png"), 0, 0, 20, 10, j2me::Sprite::TRANS_NONE);
  bonus = std::make_unique<j2me::ImageItem>("Sticky ball", img, j2me::Item::LAYOUT_LEFT | j2me::Item::LAYOUT_NEWLINE_AFTER, "");
  form->append(std::move(bonus));
  form->append("The ball \"sticks\" to the platform. Press the \"fire\" button to release it.");

  img = j2me::Image::createImage(j2me::Image::createImage("/images/bonus3.png"), 0, 0, 20, 10, j2me::Sprite::TRANS_NONE);
  bonus = std::make_unique<j2me::ImageItem>("Power ball", img, j2me::Item::LAYOUT_LEFT | j2me::Item::LAYOUT_NEWLINE_AFTER, "");
  form->append(std::move(bonus));
  form->append("The ball doesn't bounce off the bricks, instead it shoots right through them.");

  img = j2me::Image::createImage(j2me::Image::createImage("/images/bonus4.png"), 0, 0, 20, 10, j2me::Sprite::TRANS_NONE);
  bonus = std::make_unique< j2me::ImageItem>("Extra life", img, j2me::Item::LAYOUT_LEFT | j2me::Item::LAYOUT_NEWLINE_AFTER, "");
  form->append(std::move(bonus));
  form->append("Gives you an extra life.\n");
  form->append("\n");
  form->append("\nEnjoy your time with Arkanerd!");

  form->addCommand(BACK_COMMAND);
  form->setCommandListener(this);
  display_->setCurrent(std::move(form));
}

void Main::about() {
  auto form = std::make_unique< j2me::Form>(this, "About Arkanerd");
  std::string aboutText = "A little Arkanoid/Break-out like game for Java MIDP 2.0\n\n"
    "Copyright (C) 2006 Kasper Laudrup\n\n"
    "Arkanerd is free software, covered by the GNU General Public License,"
    " and you are welcome to change it and/or distribute copies of it"
    " under certain conditions.\n\n"
    "Please see http://www.linuxfan.dk for source code etc.";
  auto tempVar = std::make_unique<j2me::StringItem>(std::nullopt, aboutText);
  form->append(std::move(tempVar));
  form->addCommand(BACK_COMMAND);
  form->setCommandListener(this);
  display_->setCurrent(std::move(form));
}

} // namespace arkanerd

int main() {
  arkanerd::Main main;
  main.run();
}
