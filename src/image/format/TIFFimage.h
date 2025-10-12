#ifndef _TIFF_IMAGE_H_
#define _TIFF_IMAGE_H_

#include "../image.h"
#include "../imageRaster.h"
#include "tiffio.h"
#include <string>

#ifdef DEBUG
#include "autoCounter.h"
#endif

namespace IMAGE {

    /*TIFFimage class inherits from generic image class.TIFFimage should add all the
extra information and functionality to support the tiff format.
*/

    /////////////////////////////////////////////////////////////////////////

    class TIFFimage : public Image {
      private:
        // pointer to tiff file
        TIFF* imageFile_m;

#ifdef DEBUG
        static AutoCounter<TIFFimage> counter;
#endif

      public:
        TIFFimage() noexcept;

        ~TIFFimage() noexcept;

        // private copy-constructor and operator= to avoid passing by value
        TIFFimage(const TIFFimage&) = delete;

        TIFFimage& operator=(const TIFFimage&) = delete;

        void       open(const std::string&, const char);

        void       close();

        void       readImageRaster();

        void       writeRasterToImage();

    }; // end of class TIFFimage

} // end of namespace IMAGE

#endif
