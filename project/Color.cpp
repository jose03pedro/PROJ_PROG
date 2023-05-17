#include "Color.hpp"

namespace prog {
Color::Color() : red_(0), green_(0), blue_(0) {
    // Initializes the color to black (0, 0, 0).
}

Color::Color(const Color& other)
    : red_(other.red_), green_(other.green_), blue_(other.blue_) {
    // Copies the RGB values from another object.
}

Color::Color(rgb_value red, rgb_value green, rgb_value blue)
    : red_(red), green_(green), blue_(blue) {
    // Constructor using supplied RGB values.
}

rgb_value Color::red() const { return red_; }

rgb_value Color::green() const { return green_; }

rgb_value Color::blue() const { return blue_; }

rgb_value& Color::red() { return red_; }

rgb_value& Color::green() { return green_; }

rgb_value& Color::blue() { return blue_; }
}  // namespace prog
