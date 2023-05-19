#include "Script.hpp"

#include <fstream>
#include <iostream>

#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
// Use to read color values from a script file.
istream& operator>>(istream& input, Color& c) {
    int r, g, b;
    input >> r >> g >> b;
    c.red() = r;
    c.green() = g;
    c.blue() = b;
    return input;
}

Script::Script(const string& filename) : image(nullptr), input(filename) {}
void Script::clear_image_if_any() {
    if (image != nullptr) {
        delete image;
        image = nullptr;
    }
}
Script::~Script() { clear_image_if_any(); }

void Script::run() {
    string command;
    while (input >> command) {
        cout << "Executing command '" << command << "' ..." << endl;
        if (command == "open") {
            open();
            continue;
        }
        if (command == "blank") {
            blank();
            continue;
        }
        // Other commands require an image to be previously loaded.
        if (command == "save") {
            save();
            continue;
        }

        if (command == "fill") {
            fill();
            continue;
        }

        if (command == "invert") {
            invert();
            continue;
        }

        if (command == "to_gray_scale") {
            to_gray_scale();
            continue;
        }

        if (command == "replace") {
            replace();
            continue;
        }
        if (command == "h_mirror") {
            h_mirror();
            continue;
        }

        if (command == "v_mirror") {
            v_mirror();
            continue;
        }

        if (command == "add") {
            add();
            continue;
        }

        if (command == "replace") {
            replace();
            continue;
        }

        if (command == "crop") {
            crop();
            continue;
        }

        if (command == "rotate_left") {
            rotate_left();
            continue;
        }

        if (command == "rotate_right") {
            rotate_right();
            continue;
        }

        // TODO ...
    }
}
void Script::open() {
    // Replace current image (if any) with image read from PNG file.
    clear_image_if_any();
    string filename;
    input >> filename;
    image = loadFromPNG(filename);
}
void Script::blank() {
    // Replace current image (if any) with blank image.
    clear_image_if_any();
    int w, h;
    Color fill;
    input >> w >> h >> fill;
    image = new Image(w, h, fill);
}

void Script::save() {
    // Save current image to PNG file.
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }
    string filename;
    input >> filename;
    saveToPNG(filename, image);
}

void Script::fill() {
    // Fill rectangle (x, y, w, h) with color (r, g, b).
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }

    int x, y, w, h;
    Color fill;
    input >> x >> y >> w >> h >> fill;

    // Check if the input is valid
    if (x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > image->width() ||
        y + h > image->height()) {
        cout << "Invalid rectangle dimensions." << endl;
        return;
    }

    // Fill the specified rectangle with the provided color
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            image->at(j, i) = fill;
        }
    }
}

void Script::invert() {
    // Invert colors.
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }

    // Invert the colors of the image
    for (int i = 0; i < image->height(); i++) {
        for (int j = 0; j < image->width(); j++) {
            Color& pos = image->at(j, i);
            pos.red() = 255 - pos.red();
            pos.green() = 255 - pos.green();
            pos.blue() = 255 - pos.blue();
        }
    }
}

void Script::to_gray_scale() {
    // Convert image to grayscale.
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }

    // Convert each pixel to grayscale
    for (int i = 0; i < image->height(); i++) {
        for (int j = 0; j < image->width(); j++) {
            Color& pos = image->at(j, i);
            rgb_value gray = (pos.red() + pos.green() + pos.blue()) / 3;
            pos.red() = gray;
            pos.green() = gray;
            pos.blue() = gray;
        }
    }
}

void Script::replace() {
    Color oldColor, newColor;
    input >> oldColor >> newColor;
    for (int i = 0; i < image->height(); i++) {
        for (int j = 0; j < image->width(); j++) {
            if (compareColors(image->at(j, i), oldColor)) {
                image->at(j, i) = newColor;
            }
        }
    }
}

bool Script::compareColors(const Color& color1, const Color& color2) {
    return color1.red() == color2.red() && color1.green() == color2.green() &&
           color1.blue() == color2.blue();
}

void Script::h_mirror() {
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }

    // Iterate through each pixel in the left half of the image
    for (int i = 0; i < image->height(); i++) {
        for (int j = 0; j < image->width() / 2; j++) {
            Color& pixel = image->at(j, i);
            Color& mirroredPixel = image->at(image->width() - j - 1, i);

            // Swap the pixel colors between the left and right halves
            Color temp = pixel;
            pixel = mirroredPixel;
            mirroredPixel = temp;
        }
    }
}

void Script::v_mirror() {
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }

    // Iterate through each pixel in the top half of the image
    for (int i = 0; i < image->height() / 2; i++) {
        for (int j = 0; j < image->width(); j++) {
            Color& pixel = image->at(j, i);
            Color& mirroredPixel = image->at(j, image->height() - i - 1);

            // Swap the pixel colors between the top and bottom halves
            Color temp = pixel;
            pixel = mirroredPixel;
            mirroredPixel = temp;
        }
    }
}

void Script::add() {
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }

    Image* current_image = image;

    string filename;
    input >> filename;

    image = loadFromPNG(filename);

    if (image == nullptr) {
        cout << "Error loading image from file: " << filename << endl;
        return;
    }
    int r, g, b, x, y;
    input >> r >> g >> b >> x >> y;

    int image_width = image->width();
    int image_height = image->height();

    int current_width = current_image->width();
    int current_height = current_image->height();

    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            Color& pixel = image->at(j, i);
            if (compareColors(pixel, Color(r, g, b))) {
                continue;  // Skip the pixel if it matches the "neutral" color
            }

            int current_x = x + j;
            int current_y = y + i;

            if (current_x >= 0 && current_x < current_width && current_y >= 0 &&
                current_y < current_height) {
                Color& current_pixel = current_image->at(current_x, current_y);
                current_pixel = pixel;
            }
        }
    }

    delete image;
    image = current_image;
}

void Script::crop() {
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }

    int x, y, w, h;
    input >> x >> y >> w >> h;

    // Check if the rectangle is valid
    if (x < 0 || y < 0 || w < 0 || h < 0 || x + w > image->width() ||
        y + h > image->height()) {
        cout << "Invalid rectangle dimensions." << endl;
        return;
    }

    // Create a new image with the specified dimensions
    Image* new_image = new Image(w, h);

    // Iterate through each pixel in the image
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            Color& pixel = image->at(j, i);
            Color& new_pixel = new_image->at(j - x, i - y);

            // Replace the pixel color with the new_color
            new_pixel.red() = pixel.red();
            new_pixel.green() = pixel.green();
            new_pixel.blue() = pixel.blue();
        }
    }

    // Delete the old image and set the new image
    delete image;
    image = new_image;
}

void Script::rotate_left() {
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }

    // Create a new image with the swapped dimensions
    Image* new_image = new Image(image->height(), image->width());

    // Iterate through each pixel in the image
    for (int i = 0; i < image->height(); i++) {
        for (int j = 0; j < image->width(); j++) {
            Color& pixel = image->at(j, i);
            Color& new_pixel = new_image->at(i, image->width() - j - 1);
            // Replace the pixel color with the new_color
            new_pixel = pixel;
        }
    }

    // Delete the old image and set the new image
    delete image;
    image = new_image;
}

void Script::rotate_right() {
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }

    // Create a new image with the specified dimensions
    Image* new_image = new Image(image->height(), image->width());

    // Iterate through each pixel in the image
    for (int i = 0; i < image->height(); i++) {
        for (int j = 0; j < image->width(); j++) {
            Color& pixel = image->at(j, i);
            Color& new_pixel = new_image->at(image->height() - i - 1, j);

            // Replace the pixel color with the new_color
            new_pixel.red() = pixel.red();
            new_pixel.green() = pixel.green();
            new_pixel.blue() = pixel.blue();
        }
    }

    // Delete the old image and set the new image
    delete image;
    image = new_image;
}

}  // namespace prog
