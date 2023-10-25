#pragma once

#include "j2me/TiledLayer.h"

#include <string>

namespace arkanerd {
class TextLayer : public j2me::TiledLayer {
public:
  TextLayer(const std::string &text, int max_width);

  static constexpr int WIDTH = 16;
  static constexpr int HEIGHT = 16;
  //private Hashtable chars;
private:
  const std::string chars_ = "abcdefghijklmnopqrstuvwxyz 0123456789!;:'-_?";

		//{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
		//	'r','s','t','u','v','w','x','y','z',' ','0','1','2','3','4','5',
		//	'6','7','8','9','!',';',':','\'','-','_','?'};

};
} // namespace arkanerd
