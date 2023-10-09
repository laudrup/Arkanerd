#include "PlayerListener.h"

namespace j2me {
void PlayerListener::playerUpdate(const j2me::Player* /*player*/, const std::string& /*event*/, const char* /*data*/) {
  abort();
}

} // namespace j2me
