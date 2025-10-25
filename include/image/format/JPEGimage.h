#pragma once

#include "image/image.h"
#include "image/imageRaster.h"
#include "jpeglib.h"
#include <cstdio>

namespace IMAGE {

    class JPEGimage : public Image {
      private:
        JPEGimage(const JPEGimage&);

        JPEGimage& operator=(const JPEGimage&) {
            return *this;
        }

        FILE* imageFile_m;

      public:
        JPEGimage() noexcept;

        ~JPEGimage() noexcept;

        void open(const std::string&, const char);

        void close();

        void readImageRaster();

        void writeRasterToImage();

    }; // and of class JPEGimage

} // end of namespace IMAGE
