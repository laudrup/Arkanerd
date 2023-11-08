#include "ResourceManager.h"
#include "os_util.h"

#include <cassert>

namespace {
std::filesystem::path get_base_path() {
  return arkanerd::current_exe_path() / "res";
}

template <class ResourceType>
ResourceType* get_resource(const std::string& path, std::map<std::string, std::unique_ptr<ResourceType>>& res_holder) {
  auto it = res_holder.find(path);
  if (it == res_holder.end()) {
    auto resource = std::make_unique<ResourceType>();
    const auto full_path = get_base_path() / std::filesystem::path(path).relative_path();
    if (!resource->loadFromFile(full_path.string())) {
      throw std::runtime_error{std::string{"Unable to load: "} + full_path.string()};
    }
    const auto [new_pos, success] = res_holder.insert({path, std::move(resource)});
    assert(success);
    it = new_pos;
  }
  return it->second.get();

}

} // namespace

namespace arkanerd {

ResourceManager::ResourceManager()
  : base_path_(get_base_path()) {
}

sf::Texture* ResourceManager::getTexture(const std::string& path) {
  return get_resource<sf::Texture>(path, textures_);
}

sf::Font* ResourceManager::getFont(const std::string& path) {
  return get_resource<sf::Font>(path, fonts_);
}

} // namespace arkanerd
