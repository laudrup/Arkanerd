#pragma once

#include "Layer.h"
#include "Image.h"

namespace j2me {
class TiledLayer;

class Sprite : public Layer {
public:
  Sprite(const j2me::Image& image);
  Sprite(const j2me::Image& image, int frameWidth, int frameHeight);
  Sprite(const Sprite&);
  Sprite& operator=(const Sprite&) = delete;
  Sprite(Sprite&&) = default;
  Sprite& operator=(Sprite&&) = default;

  void paint(Graphics* g) override;
  void clear() override;
  bool collidesWith(TiledLayer* t, bool pixelLevel);
  bool collidesWith(Sprite* t, bool pixelLevel);
  void nextFrame();

  inline static constexpr int TRANS_NONE = 0;
  inline static constexpr int TRANS_ROT90 = 5;
  inline static constexpr int TRANS_ROT180 = 3;
  inline static constexpr int TRANS_ROT270 = 6;
  inline static constexpr int TRANS_MIRROR = 2;
  inline static constexpr int TRANS_MIRROR_ROT90 = 7;
  inline static constexpr int TRANS_MIRROR_ROT180 = 1;
  inline static constexpr int TRANS_MIRROR_ROT270 = 4;

protected:
  Sprite() = default;

private:
  std::vector<Image> images_;
  std::vector<Image>::const_iterator frame_;
};
} // namespace j2me
