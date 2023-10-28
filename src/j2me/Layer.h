#pragma once

namespace j2me {
class Graphics;

class Layer {
public:
  virtual ~Layer() = default;
  virtual void paint(Graphics*) = 0;
  virtual void clear() = 0;
  int getHeight() const;
  int getWidth() const;
  void setPosition(int x, int y);
  int getX();
  int getY();
  void move(int dx, int dy);
  //void setVisible(bool visible);

protected:
  Layer() = default;
  Layer(int width, int height);
  //bool visible() const;

private:
  int width_ = 0;
  int height_ = 0;
  int x_ = 0;
  int y_ = 0;
  bool visible_ = true;
};

} // namespace j2me
