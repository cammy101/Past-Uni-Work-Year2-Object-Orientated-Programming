//main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Image.h"
#include "Zoom.h"

using namespace std;

void imgStacker(std::vector<Image> &imgArray, Image &imgholder, const Image img)
{

	for (int x = 0; x < imgholder.h*imgholder.w; x++)
	{
		imgholder.pixels[x].r += img.pixels[x].r;
		imgholder.pixels[x].g += img.pixels[x].g;
		imgholder.pixels[x].b += img.pixels[x].b;
	}

	imgArray.push_back(img);

}

int main()
{
	std::cout << "************************************" << std::endl;
	std::cout << "Image Stacker / Image Scaler" << std::endl;
	std::cout << "************************************" << std::endl;

	//****************************************************
	//As an example, read one ppm file and write it out to testPPM.ppm
	//We need to specify the dimensions of the image
	//****************************************************

	Image imgholder(4592, 3056);
	Image imgeop(4592, 3056);
	Image imgSigma(4592, 3056);
	Image toBeZoomed(700, 700);
	Image zoomedImge(1500, 1500);
	std::vector<Image> imgArray;
	ReadWrite readerPPM;
	ReadWrite writerPPM;
	Blend blends;
	Zoom zoom;
	imgArray.reserve(10);
	char mainMenu;
	char blendMenu;

	toBeZoomed = readerPPM.readPPM("Images/Zoom/zIMG_1.ppm");

	/*imgArray::const_iterator it; // declare a read-only iterator
	it = vect.begin(); // assign it to the start of the vector
	while (it != vect.end()) // while it hasn't reach the end
	{
		cout << *it << " "; // print the value of the element it points to
		++it; // and iterate to the next element
	}

	cout << endl;*/


	for (int i = 0; i < 10; i++)
	{
		Image *image1 = new Image;
		std::string file = "Images/ImageStacker_set1/IMG_" + std::to_string(i + 1) + ".ppm";
		*image1 = readerPPM.readPPM(file);
		imgStacker(imgArray, imgholder, *image1);
		delete image1;
		image1 = nullptr;
	}

	cout << "All Images (10) have been read in " << endl;
	cout << "Would you like to either: " << endl;
	cout << "1. Blend Images " << endl;
	cout << "2. Zoom & Scale Images " << endl;
	cout << "3. Exit Program" << endl;
	
	cin >> mainMenu;

	switch (mainMenu)
	{
	case '1':
	{
		cout << "You have chosen to Blend images " << endl;
		cout << "Which Blending Algorithem would you like to run on the Image? " << endl;
		cout << "1. Mean Blending " << endl;
		cout << "2. Median Blending " << endl;
		cout << "3. Sigma Blending " << endl;

		cin >> blendMenu;

		switch (blendMenu)
		{

		case '1':
		{
			cout << "You have chosen Mean Blend, Please wait until the Blending proccess has finished " << endl;
			blends.imgMeanBlend(imgholder);

			cout << "Blending has now finished, now writting new Blended Image" << endl;
			writerPPM.writePPM(imgholder, "meanBlended.ppm");

			break;
		}

		case '2':
		{
			cout << "You have chosen Median Blend, Please wait until the Blending proccess has finished " << endl;
			blends.imgMedianBlend(imgArray, imgeop);

			cout << "Blending has now finished, now writting new Blended Image" << endl;
			writerPPM.writePPM(imgeop, "medianBlended.ppm");

			break;
		}

		case '3':
		{
			cout << "You have chosen Sigma Blend, Please wait until the Blending proccess has finished " << endl;
			blends.imgSigmaClip(imgArray, imgeop, imgSigma);

			cout << "Blending has now finished, now writting new Blended Image" << endl;
			writerPPM.writePPM(imgSigma, "sigmaClip.ppm");

			break;
		}
		default: cout << "Incorrect Input. Please Select 1, 2 or 3 " << endl;
		}
	}	
	case '2':
	{
		cout << "You have chosen to Zoom and Scale an image " << endl;

		zoom.x2Scale(toBeZoomed, zoomedImge);
		writerPPM.writePPM(zoomedImge, "zoomedImage.ppm");
		
	
		
		break;
	}
	case '3':
	{
		goto End;
		
	}
	default: cout << "Incorrect Input. Please Select 1, 2 or 3" << endl;

	}

End:
	cout << "Exiting Program" << endl;
	return 0;
}



