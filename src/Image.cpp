#include "Image.hpp"

namespace prog {
Image::Image(int w, int h, const Color& fill)
    : width_(w), height_(h), pixels_(w * h, fill) {}

Image::~Image() {}

int Image::width() const { return width_; }

int Image::height() const { return height_; }

Color& Image::at(int x, int y) { return pixels_[y * width_ + x]; }
// Accesses the pixel at the specified (x, y) coordinates in the image.

const Color& Image::at(int x, int y) const { return pixels_[y * width_ + x]; }
}  // namespace prog
