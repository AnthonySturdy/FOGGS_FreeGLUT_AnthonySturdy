#include "BMPLoader.h"

namespace BMPLoader {
	struct BitMap {
		unsigned int width, height;
		unsigned char* pixels;
	};

	BitMap* bmp;

	char* BMPLoader::LoadBitMap(const char* fileName) {
		//Reset bmp from previous texture
		bmp = nullptr;

		std::ifstream inFile(fileName, std::ifstream::binary);
		if (inFile.good()) {
			bmp = new BitMap();
			bmp->width = 0;
			bmp->height = 0;
			bmp->pixels = nullptr;

			unsigned char info[54] = { 0 };
			inFile.read((char*)&info[0], 54);

			bmp->width = *(unsigned int*)&info[18];
			bmp->height = *(unsigned int*)&info[22];

			unsigned long size = (bmp->width * bmp->height) * 3;
			bmp->pixels = new unsigned char[size];
			inFile.read((char*)bmp->pixels, size);
			inFile.close();

			//Change BGR to RGB
			for (int i = 0; i < size; i+=3) {
				unsigned char temp = bmp->pixels[i];
				bmp->pixels[i] = bmp->pixels[i + 2];
				bmp->pixels[i + 2] = temp;
			}

			return (char*)bmp->pixels;
		}

		return nullptr;
	}
}