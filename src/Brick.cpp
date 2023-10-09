#include "Brick.h"

#include "j2me/Image.h"
#include <iostream>

namespace arkanerd {
	Brick::Brick(int color, int type)
    : j2me::Sprite(j2me::Image::createImage("/images/brick" + std::to_string(color) + ".png"))
    , type_(type) {
		//super(1,1,getImage(),20,10);
		//System.err.println("Height: " + getCellHeight());
		//System.err.println("Width: " + getCellWidth());
		//setCell(0,0,type);
	}

	int Brick::getType() {
		return type_;
	}

} // namespace arkanerd
