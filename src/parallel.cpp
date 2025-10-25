#include "vlk/VulkanContext.h"
#include "shared.h"
#include "utils/timer.h"
#include "image/img.h"
#include <cstdlib>

int main(int argc, char** argv) {
#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_TRACE
    spdlog::set_level(spdlog::level::trace);
#elif SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    CTimer totalTimer;
    totalTimer.startTimer();

    CVulkanContext applicationContext;

    std::cout << "************************************************************" << std::endl;
    std::cout << "*                     Parallel execution                   *" << std::endl;
    std::cout << "************************************************************" << std::endl;
    std::cout << "\n\n\n";

    std::vector<std::string> imageName;

    std::stringstream        input(argv[4]);
    double                   factor;

    int                      succeded = 0;
    int                      failed   = 0;

    input >> factor;

    std::string operation(argv[3]);

    CTimer      parallelTimer;

    if (getDirFileNames(argv[1], imageName)) {
        try {
            parallelTimer.startTimer();
            for (std::vector<std::string>::iterator it = imageName.begin(); it < imageName.end(); it++) {

                std::cout << (*it) << "\n";
                IMAGE::Image* oldImage = nullptr;
                IMAGE::Image* newImage = nullptr;
                std::string   oldName  = argv[1] + (*it);
                std::string   newName  = argv[2] + (*it);
                try {

                    oldImage = IMAGE::Image::createInstance(oldName);
                    newImage = IMAGE::Image::createInstance(newName);

                    ////////////////////
                    try {
                        oldImage->open(oldName, 'r');
                        newImage->open(newName, 'w');
                        oldImage->readImageRaster();
                        newImage->raster.createRaster(oldImage->raster);

                        // check which operation to do
                        if (operation == REVERSE) {
                            IMAGE::PROCESS::reverseColor(newImage->raster);
                        } else if (operation == BRIGHTNESS) {
                            IMAGE::PROCESS::adjustBrightness(newImage->raster, atoi(argv[4]));
                        } else if (operation == CONTRAST) {
                            IMAGE::PROCESS::adjustContrast(newImage->raster, atoi(argv[4]));
                        } else if (operation == RGB2GREY) {
                            IMAGE::FILTERS::convertRGB2GREY(newImage->raster, atoi(argv[4]));
                        } else if (operation == GREY2RGB) {
                            IMAGE::FILTERS::convertGREY2RGB(newImage->raster);
                        } else if (operation == RGB2BW) {
                            IMAGE::FILTERS::convertRGB2BW(newImage->raster);
                        } else if (operation == RGB2SEPIA) {
                            IMAGE::FILTERS::convertRGB2SEPIA(newImage->raster);
                        } else if (operation == ROTATE) {
                            IMAGE::PROCESS::rotateImage(newImage->raster, argv[4]);
                        } else if (operation == ZOOM) {
                            IMAGE::PROCESS::zoomImage(newImage->raster, 1, 1, 400, 300);
                        } else if (operation == SCALE) {
                            IMAGE::PROCESS::scaleImage(newImage->raster, factor);
                        } else if (operation == BLUR) {
                            IMAGE::PROCESS::blurImage(newImage->raster, atoi(argv[4]));
                        } else {
                            std::cout << "Not a valid operation \n";
                            return EXIT_SUCCESS;
                        }

                        newImage->writeRasterToImage();
                        succeded++;

                    } catch (IMAGE::FileIoFailed& e) {
                        std::cout << e.what() << "\n";
                        failed++;
                    } catch (IMAGE::ImageFormatError& e) {
                        std::cout << e.what() << "\n";
                        failed++;
                    } catch (IMAGE::EmptyImage& e) {
                        std::cout << e.what() << "\n";
                        failed++;
                    } catch (IMAGE::EmptyRaster& e) {
                        std::cout << e.what() << "\n";
                        failed++;
                    }

                    oldImage->close();
                    newImage->close();
                    delete oldImage;
                    delete newImage;

                } catch (IMAGE::NotSupportedFormat& e) {
                    std::cout << e.what() << "\n";
                    failed++;
                }

            } // end of for

        } catch (IMAGE::BadAlloc& e) {
            std::cout << e.what() << std::endl;
            std::cout << "Exiting program...\n";
            return EXIT_FAILURE;

        } catch (...) {
            std::cout << "cought unexpected exception...\n";
            std::cout << "Exitig program...\n";
            return EXIT_FAILURE;
        }
    }
    parallelTimer.stopTimer();
    totalTimer.stopTimer();

    CTimer::printTimes(parallelTimer);

    std::cout << "\n\n\n";

    // final output
    // ////////////////////////////////////////////////////////////////////

    std::cout << "*************************************************************" << std::endl;
    std::cout << "*                          Results                          *" << std::endl;

    std::cout << std::setfill('x') << std::setw(20);
    std::cout << "* total files      :  " << imageName.size() << "                                     *" << std::endl;
    std::cout << "* Succeded images  :  " << succeded << "                                     *" << std::endl;
    std::cout << "* Failed images    :  " << failed << "                                     *" << std::endl;

    std::cout << "*                                                           *" << std::endl;

    std::cout.precision(6);
    std::cout << "* Total execution time             :  " << totalTimer.elapsedTime() << " sec           *" << std::endl;
    std::cout << "* Parallel partial execution time  :  " << parallelTimer.elapsedTime() << " sec           *" << std::endl;

    std::cout << "*                                                           *" << std::endl;
    std::cout << "*                        END OF PROGRAM                     *" << std::endl;
    std::cout << "*************************************************************" << std::endl;

    return EXIT_SUCCESS;
}
