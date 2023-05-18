#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include <vector>

#include "Color.hpp"

namespace prog {
class Image {
   private:
    int width_;
    int height_;
    vector<Color> pixels_;

   public:
    Image(int w, int h, const Color &fill = {255, 255, 255});
    ~Image();
    int width() const;
    int height() const;
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
    
};
}  // namespace prog
#endif
