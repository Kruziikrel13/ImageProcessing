#ifndef _JPEG_IMAGE_H_
#define _JPEG_IMAGE_H_

#include "../image.h"
#include "../imageRaster.h"
#include "jpeglib.h"
#include <stdio.h>

namespace IMAGE {

    class JPEGimage : public Image {
      private:
        JPEGimage(const JPEGimage&);

        JPEGimage& operator=(const JPEGimage&) {
            return *this;
        }

        FILE* imageFile_m;

#ifdef DEBUG
        static AutoCounter<JPEGimage> counter;
#endif

      public:
        JPEGimage() noexcept;

        ~JPEGimage() noexcept;

        void open(const std::string&, const char);

        void close();

        void readImageRaster();

        void writeRasterToImage();

    }; // and of class JPEGimage

} // end of namespace IMAGE

#endif
