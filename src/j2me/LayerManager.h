#pragma once

#include "Layer.h"

#include <vector>

namespace j2me {

class LayerManager {
public:
  void append(Layer* l);
  void insert(Layer* l, int index);
  void remove(Layer* l);
  void paint(Graphics* g, int x, int y);
  void clear();

private:
  std::vector<Layer*> layers_;
};

} // namespace j2me
