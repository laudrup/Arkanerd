#include "TiledLayer.h"
#include "Graphics.h"
#include "Image.h"
#include "SFML/Graphics/Rect.hpp"

namespace j2me {

TiledLayer::TiledLayer(int columns, int rows, const Image& img, int tileWidth, int tileHeight)
  : Layer(columns * tileWidth, rows * tileHeight)
  , grid_(rows, std::vector<int>(columns, 0))
  , texture_(img.texture_) {
  for (unsigned int y = 0; y < texture_.getSize().y; y += tileHeight) {
    for (unsigned int x = 0; x < texture_.getSize().x; x += tileWidth) {
      sprites_.push_back({texture_, sf::IntRect{static_cast<int>(x), static_cast<int>(y), tileWidth, tileHeight}});
    }
  }
  if (!target_.create(getWidth(), getHeight())) {
    abort();
  }
}

void TiledLayer::paint(Graphics* g) {
  for (size_t row = 0; row < grid_.size(); ++row) {
    for (size_t col = 0; col < grid_[row].size(); ++col) {
      const auto tile = grid_[row][col];
      if (tile == 0) {
        continue;
      }
      auto sprite = sprites_[tile - 1];
      sprite.setPosition(col * sprite.getLocalBounds().width, row * sprite.getLocalBounds().height);
      target_.draw(sprite);
    }
  }

  target_.display();
  sf::Sprite sprite{target_.getTexture()};
  sprite.setPosition(static_cast<float>(getX()), static_cast<float>(getY()));
  g->target_->draw(sprite);
}

void TiledLayer::clear() {
  target_.clear(sf::Color::Transparent);
}

void TiledLayer::fillCells(int col, int row, int numCols, int numRows, int tileIndex) {
  for (int x = col; x < numCols; ++x) {
    for (int y = row; y < numRows; ++y) {
      setCell(x, y, tileIndex);
    }
  }
}

void TiledLayer::setCell(int col, int row, int tileIndex) {
  grid_[row][col] = tileIndex;
}

int TiledLayer::getColumns() const {
  return static_cast<int>(grid_.front().size());
}

} // namespace j2me
