#pragma once
#include <cstdlib> 
#include <cstdio>
#include "Image.h"

class Zoom : public ReadWrite
{
public:
	void x2Scale(Image &toBeZoomed, Image &zoomedImge);
};
