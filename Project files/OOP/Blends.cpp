#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Image.h"
#include <cmath>

using namespace std;

void Blend::imgMeanBlend(Image &imgholder)
{
	for (int x = 0; x < imgholder.h*imgholder.w; x++)
	{
		imgholder.pixels[x].r /= 10;
		imgholder.pixels[x].g /= 10;
		imgholder.pixels[x].b /= 10;
	}
}

void Blend::imgMedianBlend(std::vector<Image> &imgArray, Image &imgeop)
{

	std::vector<float>r;
	std::vector<float>g;
	std::vector<float>b;

	r.resize(10);
	g.resize(10);
	b.resize(10);

	for (int p = 0; p < imgArray[0].h*imgArray[0].w; p++)
	{
		for (int i = 0; i < 10; i++)
		{
			r[i] = imgArray[i].pixels[p].r;
			g[i] = imgArray[i].pixels[p].g;
			b[i] = imgArray[i].pixels[p].b;
		}

		std::sort(r.begin(), r.end());
		std::sort(g.begin(), g.end());
		std::sort(b.begin(), b.end());

		imgeop[p].r = (r[4] + r[5]) / 2;
		imgeop[p].g = (g[4] + g[5]) / 2;
		imgeop[p].b = (b[4] + b[5]) / 2;
	}


}


Image::Rgb Blend::sdt(std::vector<Image> &imgArray)
{
	Image::Rgb deviation, sum, sum2;
	
	/*iation.r = sum2.r;
	deviation.g = sum2.g;
	deviation.b = sum2.b;*/

	for (int i = 0; i< imgArray.size(); i++)
	{
		sum += *imgArray[i].pixels;
	}
	Image::Rgb mean = sum / static_cast<float>(imgArray.size());
	for (int i = 0; i < imgArray.size(); i++)
	{
		sum2 += (*imgArray[i].pixels - mean)*(*imgArray[i].pixels - mean);
	}
	deviation.g = std::sqrt(sum2.g / static_cast<float>(imgArray.size()));
	deviation.b = std::sqrt(sum2.b / static_cast<float>(imgArray.size()));
	deviation.r = std::sqrt(sum2.r / static_cast<float>(imgArray.size()));
	return deviation;
}

void Blend::imgSigmaClip(std::vector<Image> &imgArray, Image &imgeop, Image &imgSigma)
{
	Image::Rgb sigma = 1;
	Image::Rgb sdt2;
	Image::Rgb remainingPixels;
	Image::Rgb remainingMean;
	sdt2 = sdt(imgArray);
	for (int j = 0; j < imgArray.size(); j++)
	{
		float numberOfPixels = 10;
		for (int i = 0; i < imgeop.h*imgeop.w; i++)
		{
			//Initialize the upper and lower bounds
			Image::Rgb Higher(imgeop.pixels[i] + sigma * sdt2);
			Image::Rgb Lower(imgeop.pixels[i] - sigma * sdt2);		

				if (imgArray[j].pixels[i] > Higher || imgArray[j].pixels[i] < Lower)
				{
					//Reject the pixel
					//Decrement the number of pixels each time a pixel is rejected
					numberOfPixels--;
				}
				else
				{
					remainingPixels += imgArray[j].pixels[i];
				}
			
	
			Image::Rgb remainingMean = remainingPixels / 2;

			imgSigma.pixels[j] = remainingMean;
		}
	}


}

 

