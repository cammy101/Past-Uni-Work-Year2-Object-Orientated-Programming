#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Image.h"
#include "Zoom.h"





void Zoom::x2Scale(Image &toBeZoomed, Image &zoomedImge)
{
	int width = toBeZoomed.w;
	int height = toBeZoomed.h;
	int w2 = zoomedImge.w;
	int h2 = zoomedImge.h;
	
	double x_ratio = w2 / width;
	double y_ratio = h2 / height;
	double px, py;
	for (int i = 0; i < h2; i++)
	{
		for (int j = 0; j < w2; j++)
		{
			px = (double)((int)(j / x_ratio));
			py = (double)((int)(i / y_ratio));
			zoomedImge.pixels[(i * w2) + j].r = toBeZoomed.pixels[(int)((py * width) + px)].r;
			zoomedImge.pixels[(i * w2) + j].g = toBeZoomed.pixels[(int)((py * width) + px)].g;
			zoomedImge.pixels[(i * w2) + j].b = toBeZoomed.pixels[(int)((py * width) + px)].b;
		}
	}
	
		
}

