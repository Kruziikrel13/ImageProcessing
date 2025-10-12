#pragma once

#include "processing/imageProcessing.h"
#include "image/format/JPEGimage.h"
#include "image/format/PNGimage.h"
#include "image/format/TIFFimage.h"
#include "image/image.h"
#include "image/imageRaster.h"
#include "image/imgError.h"

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
