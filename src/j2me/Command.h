#pragma once

#include <string>

namespace j2me {
class Command {
public:
  Command(const std::string& label, int commandType, int priority);
  bool operator==(const Command& other) const;
  int getCommandType() const;

  inline static constexpr int SCREEN = 0;
  inline static constexpr int BACK = 2;
  inline static constexpr int CANCEL = 3;
  inline static constexpr int OK = 4;
  inline static constexpr int HELP = 5;
  inline static constexpr int STOP = 6;
  inline static constexpr int EXIT = 7;
  inline static constexpr int ITEM = 8;

private:
  std::string label_;
  int type_;
  int priority_;
};
} // namespace j2me
