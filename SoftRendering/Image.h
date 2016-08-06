#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

class Image {
public:
	explicit Image(const char* path);
	Image::Image(int _width = 0, int _height = 0) :width(_width), height(_height) {
		image = new uint32_t[width*height];
	}

	void saveImage(const char* name) const;

	uint32_t *image;
	int width;
	int height;

	~Image() {
		delete[] image;
	}
};

#endif