#pragma once

#include "Layer.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace j2me {

class Image;

class TiledLayer : public Layer {
public:
  TiledLayer(const sf::Texture* texture, int columns, int rows, int tileWidth, int tileHeight);
  void paint(Graphics* g) override;
  void clear() override;
  void fillCells(int col, int row, int numCols, int numRows, int tileIndex);
  void setCell(int col, int row, int tileIndex);
  int getColumns() const;

private:
  std::vector<std::vector<int>> grid_;
  sf::Texture texture_;
  sf::RenderTexture target_;
  std::vector<sf::Sprite> sprites_;
};

} // namespace j2me
