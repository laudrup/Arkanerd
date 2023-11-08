#pragma once

#include <SFML/Graphics.hpp>

#include <filesystem>
#include <memory>
#include <string>

namespace arkanerd {

class ResourceManager {
public:
  ResourceManager();
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager) = delete;

  sf::Texture* getTexture(const std::string& path);
  sf::Font* getFont(const std::string& path);

private:
  std::map<std::string, std::unique_ptr<sf::Texture>> textures_;
  std::map<std::string, std::unique_ptr<sf::Font>> fonts_;
  std::filesystem::path base_path_; // TODO: Needed?
};

} // namespace arkanerd
