#include "image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace Rpm {

struct Image2D {
	int width, height, channels;
	unsigned char* data;
	bool stbiAllocated;
};


//======================================================================//
// Allocation and De-allocation
//======================================================================//
Image2D* imageInitialize(int width, int height, int channels) {
	if (width <= 0 || height <= 0 || channels <= 0) return nullptr;

	Image2D* image = new Image2D;
	if (!image) return nullptr;

	image->width = width;
	image->height = height;
	image->channels = channels;
	image->data = new unsigned char[width * height * channels];

	if (!image->data) {
		delete image;
		return nullptr;
	}

	image->stbiAllocated = false;
	return image;
}

Image2D* imageInitialize(const unsigned char* data, int width, int height, int channels)
{
	Image2D* image = imageInitialize(width, height, channels);
	if(!image) return nullptr;

	for (int y=0; y < height; y++) {
		for (int x=0; x < width; x++) {
			size_t handle;
			imageGetPixelHandle(image, x, y, handle);
			for (int i =0; i < channels; i++) {
				image->data[handle + i] = data[handle + i];
			}
		}
	}
	return image;
}

Image2D* imageLoad(const char* path, int channels) {
	Image2D* img = new Image2D;
	if (!img) return nullptr;

	img->data = stbi_load(path, &img->width, &img->height, &img->channels, channels);
	if (!img->data) {
		delete img;
		return nullptr;
	}

	img->stbiAllocated = true;
	return img;
}

void imageFree(Image2D* image) {
	if (!image) return;

	if (image->data) {
		if (image->stbiAllocated) {
			stbi_image_free(image->data);
		} else {
			delete[] image->data;
		}
		image->data = nullptr;
	}

	delete image;
}

//======================================================================//
// Image Modification
//======================================================================//
Image2D* imageUpscale(const Image2D* original, int ratio)
{
	if (ratio <= 1) return nullptr;


	int new_width = original->width * ratio;
	int new_height = original->height * ratio;
	Image2D* result_image = imageInitialize(new_width, new_height, original->channels);

	for (int y=0; y < new_height; y++) {
		int y_original = y / ratio;

		for (int x=0; x < new_width; x++) {
			int x_original = x / ratio;

			size_t handle1, handle2;
			imageGetPixelHandle(result_image, x, y, handle1);
			imageGetPixelHandle(original, x_original, y_original, handle2);

			for (int i=0; i<original->channels; i++)
				result_image->data[handle1 + i] = original->data[handle2 + i];
		}
	}

	return result_image;
}

bool imageGetPixelHandle(const Image2D* image, int x, int y, size_t& handle) {
	if (!image || x < 0 || y < 0 || x >= image->width || y >= image->height) return false;

	handle = size_t((y * image->width + x) * image->channels);
	return true;
}

bool imageWritePixel(const Image2D* image, size_t handle, unsigned char value) {
	if (!image || !image->data || handle >= size_t(image->width * image->height * image->channels))
		return false;

	image->data[handle] = value;
	return true;
}

//======================================================================//
// Getters and Setters
//======================================================================//
bool imageGetSpecification(const Image2D* image, ImageSpec spec, float& data) {
	if (!image) return false;

	switch (spec) {
		case ImageSpec::WIDTH: data = float(image->width); break;
		case ImageSpec::HEIGHT: data = float(image->height); break;
		case ImageSpec::NUM_CHANNELS: data = float(image->channels); break;
		default: return false;
	}

	return true;
}

unsigned char* imageGetData(const Image2D* image) {
	return image ? image->data : nullptr;
}

bool imageSavePng(const Image2D* image, const char* path) {
	if (!image || !image->data) {
		return false;
	}

	int success = stbi_write_png(path, image->width, image->height, image->channels, image->data, image->width * image->channels);

	return success != 0;
}

} // NAMESPACE RPM
