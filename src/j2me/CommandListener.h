#pragma once

namespace j2me {

class Command;
class Displayable;

class CommandListener {
public:
  virtual ~CommandListener() = default;
  virtual void commandAction(const j2me::Command& cmd, const j2me::Displayable& dsp);
};

} // namespace j2me
