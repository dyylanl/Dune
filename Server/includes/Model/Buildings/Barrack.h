#ifndef __BARRACKS_H__
#define __BARRACKS_H__

#include "Building.h"

class Barracks : public Building {
public:
	Barracks(const int x, const int y, int blockWidth, int blockHeight);
	~Barracks();
};

#endif	// __BARRACKS_H__
