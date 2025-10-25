#include "image/format/PNGimage.h"
#include <cstdlib>
#include <cstring>

namespace IMAGE {

    PNGimage::PNGimage() noexcept : imageFile_m(nullptr) {}

    PNGimage::~PNGimage() noexcept {}

    void PNGimage::open(const std::string& name, const char mode) {

        name_m = name;
        // read mode
        if (mode == 'r')
            imageFile_m = fopen(name.c_str(), "rb");
        // write mode
        else if (mode == 'w')
            imageFile_m = fopen(name.c_str(), "wb");

        if (!imageFile_m)
            throw IMAGE::FileIoFailed("Could not open file " + name); // failed to
                                                                      // open

        // read mode
        if (mode == 'r') {

            char   header[8]; // 8 is the maximum size that can be checked

            size_t bytesRead = fread(header, 1, 8, imageFile_m);
            if (bytesRead != 8) {
                throw IMAGE::FileIoFailed("Failed to read PNG header from file " + name_m);
            }
            if (png_sig_cmp((unsigned char*)header, 0, 8))
                throw IMAGE::ImageFormatError("PNG internal error in image   " + name_m);

            /* initialize stuff */
            png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

            if (!png_ptr)
                throw IMAGE::ImageFormatError("PNG internal error in image   " + name_m);

            info_ptr = png_create_info_struct(png_ptr);
            if (!info_ptr)
                throw IMAGE::ImageFormatError("PNG internal error in image   " + name_m);

            if (setjmp(png_jmpbuf(png_ptr)))
                throw IMAGE::ImageFormatError("PNG internal error in image   " + name_m);

            png_init_io(png_ptr, imageFile_m);
            png_set_sig_bytes(png_ptr, 8);

            png_read_info(png_ptr, info_ptr);

            raster.setWidth(png_get_image_width(png_ptr, info_ptr));
            raster.setHeight(png_get_image_height(png_ptr, info_ptr));
            color_type = png_get_color_type(png_ptr, info_ptr);
            bit_depth  = png_get_bit_depth(png_ptr, info_ptr);

            if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
                raster.setSamplesPerPixel(3);

            else if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGBA)
                raster.setSamplesPerPixel(4);

            num_of_passes = png_set_interlace_handling(png_ptr);
            png_read_update_info(png_ptr, info_ptr);

        } // and of read mode

        // write mode
        else if (mode == 'w') {
            png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

            if (!png_ptr)
                throw IMAGE::ImageFormatError("PNG internal error in image   " + name_m);

            info_ptr = png_create_info_struct(png_ptr);
            if (!info_ptr)
                throw IMAGE::ImageFormatError("PNG internal error in image   " + name_m);

            if (setjmp(png_jmpbuf(png_ptr)))
                throw IMAGE::ImageFormatError("PNG internal error in image   " + name_m);
        }
    }

    void PNGimage::close() {
        if (imageFile_m)
            fclose(imageFile_m);
    }

    void PNGimage::readImageRaster() {

        if (!imageFile_m)
            throw IMAGE::EmptyImage("Tried to read from unopened image " + name_m);

        try {
            this->raster.createRaster();
        } catch (IMAGE::BadAlloc& e) { throw IMAGE::BadAlloc("Not enough memory for image   " + name_m); }

        unsigned int   width   = raster.getWidth();
        unsigned int   height  = raster.getHeight();
        unsigned int   samples = raster.getSamplesPerPixel();
        unsigned char* ptr     = raster.getRasterPointer();

        if (setjmp(png_jmpbuf(png_ptr)))
            throw IMAGE::ImageFormatError("PNG internal error in image   " + name_m);
        png_bytep* row_pointers;

        row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
        for (unsigned int y = 0; y < height; y++)
            row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));

        png_read_image(png_ptr, row_pointers);

        // rows are read from top to bottom
        for (int i = 0, j = height - 1; (unsigned int)i < height && j >= 0; i++, j--) {
            memcpy(&ptr[j * width * samples], row_pointers[i], width * samples);
            free(row_pointers[i]);
        }
        free(row_pointers);
    }

    void PNGimage::writeRasterToImage() {

        if (!raster.hasRaster())
            throw IMAGE::EmptyRaster("Raster of image " + name_m + " is empty");

        png_init_io(png_ptr, imageFile_m);

        if (setjmp(png_jmpbuf(png_ptr)))
            throw IMAGE::ImageFormatError("PNG internal error in image   " + name_m);

        unsigned int   width   = raster.getWidth();
        unsigned int   height  = raster.getHeight();
        unsigned int   samples = raster.getSamplesPerPixel();
        unsigned char* ptr     = raster.getRasterPointer();

        if (samples == 4)
            color_type = PNG_COLOR_TYPE_RGBA;
        else if (samples == 3)
            color_type = PNG_COLOR_TYPE_RGB;

        bit_depth = 8; // standard value for bit_depth

        png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

        png_write_info(png_ptr, info_ptr);

        /* write bytes */
        if (setjmp(png_jmpbuf(png_ptr)))
            throw IMAGE::ImageFormatError("PNG internal error in image   " + name_m);

        png_bytep* row_pointers;

        row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
        for (unsigned int y = 0; y < height; y++)
            row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));

        for (unsigned int i = 0, j = height - 1; i < height; i++, j--)
            memcpy(row_pointers[i], &ptr[j * width * samples], width * samples);

        png_write_image(png_ptr, row_pointers);

        /* end write */
        if (setjmp(png_jmpbuf(png_ptr)))
            throw IMAGE::ImageFormatError("PNG internal error in image   " + name_m);
        png_write_end(png_ptr, nullptr);

        /* cleanup heap allocation */
        for (unsigned int y = 0; y < height; y++)
            free(row_pointers[y]);
        free(row_pointers);
    }

} // namespace IMAGE
