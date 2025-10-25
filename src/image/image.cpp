#include "image/image.h"
#include "image/format/JPEGimage.h"
#include "image/format/PNGimage.h"
#include "image/format/TIFFimage.h"
#include <iostream>
#include <string>


namespace IMAGE {

    /*Public functions*/
    Image::Image() noexcept {}
    Image::~Image() noexcept {}

    Image* Image::createInstance(const std::string& s) {

        // chekcing if the format image is supported

        try {
            if (s.find(".tiff") != std::string::npos)
                return new IMAGE::TIFFimage();

            else if (s.find(".jpeg") != std::string::npos || s.find(".jpg") != std::string::npos || s.find(".JPEG") != std::string::npos || s.find(".JPG") != std::string::npos)
                return new IMAGE::JPEGimage();

            else if (s.find(".png") != std::string::npos)
                return new IMAGE::PNGimage();

            else // not supported format . throw exception
                throw IMAGE::NotSupportedFormat("Format of  " + s + "   is not supported");
        } catch (std::bad_alloc& e) { throw IMAGE::BadAlloc("Not enough memory to create image    " + s); }
        return nullptr;
    }

} // namespace IMAGE
