#include "Main.h"
#include "ArkanerdCanvas.h"
#include "TextCanvas.h"
#include "MenuCanvas.h"
#include "TitleCanvas.h"

#include "j2me/Display.h"

namespace arkanerd {

Main::Main()
  : display_(j2me::Display::getDisplay(this))
  , settings_(std::make_unique<Settings>()) {

  auto title = std::make_unique<TitleCanvas>(this, [this]() {
    showMenu();
  });
  display_->setCurrent(std::move(title));
}

void Main::commandAction(const j2me::Command&, const j2me::Displayable& /*dsp*/) {
}

void Main::showMenu() {
    std::vector<MenuCanvas::Entry> entries {
    {"New game", [this]() {
      newGame();
    }},
    {"Instructions", [this]() {
      instructions();
    }},
    {"High scores", [this]() {
      highScores();
    }},
    {"Settings", [this]() {
      settings();
    }},
    {"About", [this]() {
      about();
    }}
  };

  display_->setCurrent(std::make_unique<MenuCanvas>(this, "Arkanerd", entries, []() {
    // Exit game
  }));
}

void Main::gameComplete(int points) {
  TextCanvas::items_type items{
    "You did it!\n"
    "You completed all leves!\n"
    "Please go to http://www.linuxfan.dk\n"
    "To look for more levels\n",
    getScoreString(points)
  };

  display_->setCurrent(std::make_unique<TextCanvas>(this, "Game completed!", items, [this]() {
    showMenu();
  }));
}

void Main::gameOver(int points) {
  TextCanvas::items_type items{
    getScoreString(points)
  };

  display_->setCurrent(std::make_unique<TextCanvas>(this, "Game over!", items, [this]() {
    showMenu();
  }));
}

void Main::newGame() {
  auto canvas = std::make_unique<ArkanerdCanvas>(this, settings_.get());
  display_->setCurrent(std::move(canvas));
  dynamic_cast<ArkanerdCanvas*>(display_->getCurrent())->nextLevel();
}

std::string Main::getScoreString(int score) {
  if (score > settings_->getHighScore()) {
    settings_->setHighScore(score);
    return std::string{
      "Congratulations!\n"
      "You got a new High Score:\n"}
      + std::to_string(score);
  } else {
    return std::string{
      "Your Score:\n"}
      + std::to_string(score)
      + "\nHigh Score:\n"
      + std::to_string(settings_->getHighScore());
  }
}

void Main::settings() {
  std::vector<MenuCanvas::Entry> entries {
    {"Enable music", []() {
    }}
  };

  display_->setCurrent(std::make_unique<MenuCanvas>(this, "Settings", entries, [this]() {
    showMenu();
  }));
}

void Main::highScores() {
  const std::string text = "High score: " + std::to_string(settings_->getHighScore());
  TextCanvas::items_type items{text};

  display_->setCurrent(std::make_unique<TextCanvas>(this, "High Score", items, [this]() {
    showMenu();
  }));
}

void Main::instructions() {
  TextCanvas::items_type items{
    "Arkanerd is a little Arkanoid/Break-out like game.\n\n"
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
    "The special powerup bonuses are:",
    TextCanvas::ImageItem{
      j2me::Image::createImage(j2me::Image::createImage(resources.getTexture("/images/bonus1.png")), 0, 0, 20, 10, j2me::Sprite::TRANS_NONE),
      "100 Points"
    },
    "Adds 100 points to the current score.",
    TextCanvas::ImageItem{
      j2me::Image::createImage(j2me::Image::createImage(resources.getTexture("/images/bonus2.png")), 0, 0, 20, 10, j2me::Sprite::TRANS_NONE),
      "Sticky ball"},
    "The ball \"sticks\" to the platform. Press the \"fire\" button to release it.",
    TextCanvas::ImageItem{
      j2me::Image::createImage(j2me::Image::createImage(resources.getTexture("/images/bonus3.png")), 0, 0, 20, 10, j2me::Sprite::TRANS_NONE),
      "Power ball"},
    "The ball doesn't bounce off the bricks, instead it shoots right through them.",
    TextCanvas::ImageItem{j2me::Image::createImage(j2me::Image::createImage(resources.getTexture("/images/bonus4.png")), 0, 0, 20, 10, j2me::Sprite::TRANS_NONE),
      "Extra life"},
    "Gives you an extra life.\n",
    "Enjoy your time with Arkanerd!\n"
  };

  display_->setCurrent(std::make_unique<TextCanvas>(this, "Instructions", items, [this]() {
    showMenu();
  }));
}

void Main::about() {
  const std::string text = "A little Arkanoid/Break-out like game for Java MIDP 2.0\n\n"
    "Copyright (C) 2006 Kasper Laudrup\n\n"
    "Arkanerd is free software, covered by the GNU General Public License,"
    " and you are welcome to change it and/or distribute copies of it"
    " under certain conditions.\n\n"
    "Please see http://www.linuxfan.dk for source code etc.";

  TextCanvas::items_type items{text};

  display_->setCurrent(std::make_unique<TextCanvas>(this, "About Arkanerd", items, [this]() {
    showMenu();
  }));
}

} // namespace arkanerd

int main() {
  arkanerd::Main main;
  main.run();
}
