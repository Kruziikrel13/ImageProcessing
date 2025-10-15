#pragma once

#include "image/imageRaster.h"

namespace IMAGE {

    class ImageRaster;

    namespace PROCESS {

        void convertRGB2GREY(const IMAGE::ImageRaster&);

        void converGREY2RGB(const IMAGE::ImageRaster&);

        void convertRGB2BW(const IMAGE::ImageRaster&);

        void convertRGB2SEPIA(const IMAGE::ImageRaster&);

        int  rotateImage(IMAGE::ImageRaster&);

    } // end of namespace PROCESS

} // namespace IMAGE
