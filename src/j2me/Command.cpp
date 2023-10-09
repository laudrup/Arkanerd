#include "Command.h"

namespace j2me {

Command::Command(const std::string& label, int commandType, int priority)
  : label_(label)
  , type_(commandType)
  , priority_(priority) {
}

bool Command::operator==(const Command& other) const {
  return
    label_ == other.label_ &&
    type_ == other.type_ &&
    priority_ == other.priority_;
}

int Command::getCommandType() const {
  return type_;
}

} // namespace j2me
