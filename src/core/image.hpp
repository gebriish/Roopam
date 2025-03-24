//=================================================================
// - Image utility object that allows you to load, edit and save
//   raw image data
//=================================================================

#pragma once
#include <cstdlib>

namespace Rpm {

enum class ImageSpec {
	WIDTH,
	HEIGHT,
	NUM_CHANNELS,
};

struct Image2D;

Image2D* imageLoad(const char* path, int channels = 0);
Image2D* imageInitialize(int width, int height, int channels);
Image2D* imageInitialize(const unsigned char* data, int width, int height, int channels);
void imageFree(Image2D* image);

Image2D* imageUpscale(const Image2D* original, int ratio);
bool imageSavePng(const Image2D* image, const char* path);
bool imageGetPixelHandle(const Image2D* image, int x, int y, size_t& handle);
bool imageGetSpecification(const Image2D* image, ImageSpec spec, float& data);
bool imageWritePixel(const Image2D* image, size_t handle, unsigned char value);
unsigned char* imageGetData(const Image2D* image);

} // NAMESPACE RPM
