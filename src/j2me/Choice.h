#pragma once

namespace j2me {
class Choice {
public:
  inline static constexpr int EXCLUSIVE = 1;
  inline static constexpr int MULTIPLE = 2;
  inline static constexpr int IMPLICIT = 3;
  inline static constexpr int POPUP = 4;
  inline static constexpr int TEXT_WRAP_DEFAULT = 0;
  inline static constexpr int TEXT_WRAP_ON = 1;
  inline static constexpr int TEXT_WRAP_OFF = 2;
};
} // namespace j2me
