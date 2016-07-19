#include "Texture.h"

#include <cstring>
#include <cstdlib>

#include "Image.h"

Color Texture::sample(float u, float v) const {
	if (texture == NULL) {
		return Color();
	}
	int U = abs(int(u*(width - 1)));
	int V = abs(int(v*(height - 1)));

	uint32_t colorValue = texture[V*width + U];

	return Color(colorValue);
}

void Texture::translateFromImage(const Image & image) {
	uint32_t *tempTexture = new uint32_t[image.height*image.width];
	memcpy(tempTexture, image.image, image.height*image.width);

	if (texture != NULL) {
		delete[] texture;
	}
	
	texture = tempTexture;
	width = image.width;
	height = image.height;
}
