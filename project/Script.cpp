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

void Script::invert() {
    // Transforms each individual pixel (r, g, b) to (255-r,255-g,255-b).
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }
    image->invert();
}

void Script::save() {
    // Save current image to PNG file.
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }
    string filename;
    input >> filename;
    saveToPNG(image, filename);
}

void Script::replace() {
    // Replace color c1 with color c2.
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }
    Color c1, c2;
    input >> c1 >> c2;
    image->replace(c1, c2);
}

void Script::h_mirror() {
    // Horizontal mirror.
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }
    image->h_mirror();
}

void Script::v_mirror() {
    // Vertical mirror.
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }
    image->v_mirror();
}

void Script::add() {
    // Add two images.
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }
    string filename;
    input >> filename;
    Image* image2 = loadFromPNG(filename);
    if (image2 == nullptr) {
        cout << "Could not load image from file '" << filename << "'." << endl;
        return;
    }
    image->add(*image2);
    delete image2;
}

void Script::crop() {
    // Crop image to rectangle (x, y, w, h).
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }
    int x, y, w, h;
    input >> x >> y >> w >> h;
    image->crop(x, y, w, h);
}

void Script::rotate_left() {
    // Rotate image left.
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }
    image->rotate_left();
}

void Script::rotate_right() {
    // Rotate image right.
    if (image == nullptr) {
        cout << "No image loaded." << endl;
        return;
    }
    image->rotate_right();
}


void Script::fill() {
    clear_image_if_any();
    int w, h;
    Color fill;
    input >> w >> h >> fill;
    image = new Image(w, h, fill);
}

}  // namespace prog
