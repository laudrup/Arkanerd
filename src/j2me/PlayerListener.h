#pragma once

#include "Player.h"

#include <string>

namespace j2me {
class PlayerListener {
public:
  virtual ~PlayerListener() = default;

  inline static const std::string STARTED = "started";
  inline static const std::string STOPPED = "stopped";
  inline static const std::string END_OF_MEDIA = "endOfMedia";
  inline static const std::string DURATION_UPDATED = "durationUpdated";
  inline static const std::string DEVICE_UNAVAILABLE = "deviceUnavailable";
  inline static const std::string DEVICE_AVAILABLE = "deviceAvailable";
  inline static const std::string VOLUME_CHANGED = "volumeChanged";
  inline static const std::string ERROR = "error";
  inline static const std::string CLOSED = "closed";

protected:
  virtual void playerUpdate(const j2me::Player* player, const std::string& event, const char* data);

};
} // namespace j2me
