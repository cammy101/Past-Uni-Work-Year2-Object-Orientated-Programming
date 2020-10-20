#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Image.h"

using namespace std;

//Read ppm files into the code
//They need to be in 'binary' format (P6) with no comments in the header
//The first line is the 'P'number - P6 indicates it is a binary file, then the image dimensions and finally the colour range
//This header is then followed by the pixel colour data
//eg:	P6
//		3264 2448
//		255
//Open a .ppm file in notepad++ to see this header (caution: they are large files!)
Image ReadWrite::readPPM(std::string filename)
{
	//Remove this cout to prevent multiple outputs
	std::cout << "Reading image ..." << std::endl;
	std::ifstream ifs;
	ifs.open(filename, std::ios::binary);
	Image src;
	try {
		if (ifs.fail()) {
			throw("Can't open the input file - is it named correctly/is it in the right directory?");
		}
		std::string header;
		int w, h, b;
		ifs >> header;
		if (strcmp(header.c_str(), "P6") != 0) throw("Can't read the input file - is it in binary format (Has P6 in the header)?");
		ifs >> w >> h >> b;
		src.w = w;
		src.h = h;
		//std::cout << w << " " << h << std::endl;
		src.pixels = new Image::Rgb[w * h]; // this is throw an exception if bad_alloc 
		ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data 
		unsigned char pix[3]; // read each pixel one by one and convert bytes to floats 
		for (int i = 0; i < w * h; ++i) {
			ifs.read(reinterpret_cast<char *>(pix), 3);
			src.pixels[i].r = pix[0] / 255.f;
			src.pixels[i].g = pix[1] / 255.f;
			src.pixels[i].b = pix[2] / 255.f;
		}
		ifs.close();
	}
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ifs.close();
	}

	//Confirm image read
	//Delete this to prevent multiple lines output
	std::cout << "Image read" << std::endl;
	return src;
}

//Write data out to a ppm file
//Constructs the header as above
void ReadWrite::writePPM(const Image &img, const char *filename)
{
	//std::cout << filename << std::endl;
	std::cout << "Writing image ..." << std::endl;
	if (img.w == 0 || img.h == 0) { fprintf(stderr, "Can't save an empty image\n"); return; }
	std::ofstream ofs;
	try {
		ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users 
		if (ofs.fail()) throw("Can't open output file");
		ofs << "P6\n" << img.w << " " << img.h << "\n255\n";
		//std::cout << "P6\n" << img.w << " " << img.h << "\n255\n";
		unsigned char r, g, b;
		// loop over each pixel in the image, clamp and convert to byte format
		for (int i = 0; i < img.w * img.h; ++i) {
			r = static_cast<unsigned char>(std::min(1.f, img.pixels[i].r) * 255);
			g = static_cast<unsigned char>(std::min(1.f, img.pixels[i].g) * 255);
			b = static_cast<unsigned char>(std::min(1.f, img.pixels[i].b) * 255);
			ofs << r << g << b;
		}
		ofs.close();
		//Confirm image write
		std::cout << "Image written" << std::endl;
	}
	catch (const char *err) {
		fprintf(stderr, "%s\n", err);
		ofs.close();
	}
}

/*void ReadWrite::imgInfo()
{
	cout << "Writing LogFile" << endl;
	// assigns where to save the file
	ofstream Output;
	Output.open("LogFile.txt");
	// prints out the header infomation from the .ppm file
	Output << "Image statistics for: " << fileName << "\n";
	Output << "Header: " << h << "\n";
	Output << "Width: " << w << "\n";
	Output << "Height: " << h << "\n";
	Output << "Size: " << size << "\n";
	Output << "Max value: " << maxValue << "\n";

	cout << "File has been written" << endl;
}*/


const Image::Rgb Image::kBlack = Image::Rgb(0);
const Image::Rgb Image::kWhite = Image::Rgb(1);
const Image::Rgb Image::kRed = Image::Rgb(1, 0, 0);
const Image::Rgb Image::kGreen = Image::Rgb(0, 1, 0);
const Image::Rgb Image::kBlue = Image::Rgb(0, 0, 1);