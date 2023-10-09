#pragma once

namespace j2me {

class PlayerListener;

class Player {
public:
  int getState() const;
  void start();
  void stop();
  void close();
  void addPlayerListener(PlayerListener* playerListener);

  inline static constexpr int STARTED = 400;
};

} // namespace j2me
