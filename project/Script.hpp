#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <fstream>
#include <string>

#include "Image.hpp"

namespace prog {
class Script {
   public:
    Script(const std::string &filename);
    ~Script();
    void run();

   private:
    // Current image.
    Image *image;
    // Input stream for reading script commands.
    ifstream input;

   private:
    // Private functions
    void clear_image_if_any();
    void open();
    void blank();
    void save();
    void fill();
    void replace();
    void h_mirror();
    void v_mirror();
    void add();
    void crop();
    void rotate_left();
    void rotate_right();
    void invert();
};
}  // namespace prog
#endif
