#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>

#include "Color.h"
#include "Image.h"

class Texture {
public:
	explicit Texture(const char* path);
	explicit Texture(const Image& img);

	void renewData(const Image& img);
	Color sample(float u, float v) const;

	~Texture() {
		delete[] texture;
	}

private:
	uint32_t *texture;
	int width;
	int height;

	void translateFromImage(const Image& image);
};

inline
void Texture::renewData(const Image& img) {
	translateFromImage(img);
}

inline
Texture::Texture(const Image & img) {
	translateFromImage(img);
}

inline
Texture::Texture(const char * path) {
	Image img(path);
	translateFromImage(img);
}

#endif