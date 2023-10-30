#include "ResourceManager.h"

#include <cassert>

namespace {
std::filesystem::path get_base_path() {
  return std::filesystem::read_symlink("/proc/self/exe").parent_path() / "res";
}
} // namespace

namespace arkanerd {

ResourceManager::ResourceManager()
  : base_path_(get_base_path()) {
}

sf::Texture* ResourceManager::getTexture(const std::string& path) {
  auto it = textures_.find(path);
  if (it == textures_.end()) {
    auto texture = std::make_unique<sf::Texture>();
    const auto full_path = base_path_ / std::filesystem::path(path).relative_path();
    if (!texture->loadFromFile(full_path.string())) {
      throw std::runtime_error{std::string{"Unable to load: "} + full_path.string()};
    }
    const auto [new_pos, success] = textures_.insert({path, std::move(texture)});
    assert(success);
    it = new_pos;
  }
  return it->second.get();
}

} // namespace arkanerd
