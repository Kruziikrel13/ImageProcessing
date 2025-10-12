#ifndef _PNGIMAGE_H_
#define _PNGIMAGE_H_

#include "../image.h"
#include "png.h"

namespace IMAGE {

    class PNGimage : public Image {
      private:
        // png specific data
        png_byte    color_type;

        png_byte    bit_depth;

        png_structp png_ptr;

        png_infop   info_ptr;

        int         num_of_passes;

        FILE*       imageFile_m;

        // private copy constructor and operator =
        PNGimage(const PNGimage&);

        PNGimage& operator=(const PNGimage&) {
            return *this;
        }
#ifdef DEBUG
        static AutoCounter<PNGimage> counter;
#endif
      public:
        PNGimage() noexcept;

        ~PNGimage() noexcept;

        void open(const std::string&, const char);

        void close();

        void readImageRaster();

        void writeRasterToImage();

    }; // and of class PNGimage

} // end of namespace IMAGE

#endif
