#include "LayerManager.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>

namespace j2me {

void LayerManager::append(Layer* l) {
  layers_.push_back(l);
}

void LayerManager::remove(Layer* l) {
  const auto it = std::find(layers_.begin(), layers_.end(), l);
  if (it != layers_.end()) {
    layers_.erase(it);
  }
}

void LayerManager::paint(Graphics* g, int, int) {
  for (auto l : layers_) {
    l->paint(g);
  }
}

void LayerManager::clear() {
  for (auto l : layers_) {
    l->clear();
  }
}

} // namespace j2me
