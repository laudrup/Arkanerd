#include "MIDlet.h"
#include "Displayable.h"
#include "GameCanvas.h"
#include "Graphics.h"

namespace j2me {

void MIDlet::notifyDestroyed() {
}

int MIDlet::run() {
  startApp();
  auto& window = display_.window_;
  while (window.isOpen()) {
    auto displayable = display_.getCurrent();
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed: {
          displayable->handleKey(event.key.code);
          break;
        }
          /*
        case sf::Event::KeyReleased: {
          auto key = translate_key(event.key.code);
          if (key) {
            m_oKaperCanvas->keyReleased(*key);
          }
          break;
        }
          */
        default:
          break;
      }
    }
    window.clear(sf::Color::Red);
    j2me::Graphics g{&window};
    displayable->handlePaint(&g);
    if (auto game_canvas = dynamic_cast<GameCanvas*>(displayable); game_canvas != nullptr) {
      game_canvas->update();
    }
    window.display();
  }
  return EXIT_SUCCESS;
}

} // namespace j2me