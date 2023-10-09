#include "CommandListener.h"

#include <cstdlib>

namespace j2me {
void CommandListener::commandAction(const j2me::Command& /*cmd*/, const j2me::Displayable& /*dsp*/) {
  abort();
}

} // namespace j2me
