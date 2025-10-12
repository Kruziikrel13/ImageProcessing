#ifndef _IMG_H_
#define _IMG_H_

#include "../processing/imageProcessing.h"
#include "format/JPEGimage.h"
#include "format/PNGimage.h"
#include "format/TIFFimage.h"
#include "image.h"
#include "imageRaster.h"
#include "imgError.h"

const std::string BRIGHTNESS("-brightness");
const std::string REVERSE("-reverse");
const std::string CONTRAST("-contrast");
const std::string RGB2GREY("-rgb2grey");
const std::string GREY2RGB("-grey2rgb");
const std::string RGB2BW("-rgb2bw");
const std::string RGB2SEPIA("-rgb2sepia");
const std::string ROTATE("-rotate");
const std::string ZOOM("-zoom");
const std::string SCALE("-scale");
const std::string BLUR("-blur");

#endif
