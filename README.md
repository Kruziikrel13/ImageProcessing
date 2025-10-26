Parallel Image Processing using C++
===================================

The project explores the advantages of Vulkan multithreading in image processing while comparing between two different implementations. Several image processing functions have been implemented and are available in each implementation for comparison.

OpenMP is also used in the parallel implementation to parallelize the main program loop and process images concurrently on the CPU. Whereby the main program can then instantiate several Vulkan command buffers to process images on the GPU which will parallelize the actual pixel processing operations.

Timers are used in all implementations in order to accurately measure the difference of implementations. At the end of each execution, times are printed to stdout;

Hardware Requirements
---------------------
The program was developed and tested on two systems with the following specifications;

If in doubt, use of a more modern AMD GPU is recommended as AMD has better support for Vulkan than NVIDIA.

- System 1:
  - `OS`: Linux (NixOS)
  - `CPU`: AMD Ryzen 9 5900X
  - `GPU`: AMD Radeon RX 6800 XT

- System 2:
  - `OS`: Linux (NixOS) 
  - `CPU`: AMD Ryzen 7 9800X3D
  - `GPU`: AMD Radeon RX 9070 XT

Building
--------
All programs in the project can be built by running the below as CMake will generate the required Makefiles.
```sh
$ make all
```
The resultant built programs and artefacts will all be located in `build/`

Serial implementation
--------------------

In order to see the advantages of multithreading, the first execution mode is serial where a single operation is applied to a number of images and the processing is performed on a single thread.

Vulkan Implementation
---------------------
The vulkan implementation uses the Vulkan API to perform image processing on the GPU. Certain parts of the image processing are handed off to the GPU through the use of compute shaders.

Dependencies
------------
Build tools and library dependencies.
### Build Tools
- [gcc v14.3.0](https://gcc.gnu.org/)
- [gnumake](https://www.gnu.org/software/make/)
- [CMake >= v3.30](https://cmake.org/)
- [Vulkan SDK](https://github.com/KhronosGroup/Vulkan-Headers)
- [Shader Slang](https://github.com/shader-slang/slang)

### Libraries
All libraries specified should be installed and on `$INCLUDE_PATH` and `$LD_LIBRARY_PATH` in order for the programs to build and run correctly.

#### Common Libraries
- libtiff
- libpng
- libjpeg
- [spdlog](https://github.com/gabime/spdlog)

#### Parallel Libraries
- [Vulkan Headers](https://github.com/KhronosGroup/Vulkan-Headers)
- [OpenMP](https://openmp.llvm.org/)

Execution
---------

Two different executables will be generated in the `build/` folder. `serial` and `parallel`.

Additionally, for parallel, a shaderfile will be compiled at `build/shaders/processors.spv`. When executing the parallel executable, always ensure processors.spv is located at shaders/processors.spv relative to the execution path.
You will have the easiest time just copying the input images into build/ and executing the program from inside build/ as processors.spv will then be located at shaders/processors.spv relative to the execution path.

The following image processing functions are provided for comparison.
- reverse color
- adjust brightness
- adjust contrast
- convert RGB to Grey
- convert Grey to RGB
- convert RGB to Black and White
- convert RGB to Sepia
- rotate
- scale
- blur

The more intense the processing is the more the advantages of multithreading can be seen. For example, in order to reverse the colors of an image, all that is required is to invert the value of individual pixels which is not very computationaly intensive. On the other hand, trying to blur an image which performs a much more complex operation on each pixel is more intensive thus computing multiple pixels at a time is required for a more reasonable processing time to be achieved.

#### Running the program
Both implementations require an input folder, containing one or more images, and an output folder (must already exist, it won't be auto created) where the processed images will be stored. In addition to these the operation to perform on all images in the input folder must be specified. Usage of the program generally follows the below format.
```sh
./program input/folder/ output/folder/ -operation (-arg|numeric_arg)
```
Here are a few examples. Folder arguments should always end with a slash.

Rotate all images in the input folder to the left
```sh
$ ./program input/folder/ output/folder/ -rotate -left
```
Blur all images in the input folder by 90%
```sh
$ ./program input/folder/ output/folder/ -blur 90
```
Convert all images to black and white
```sh
$ ./program input/folder/ output/folder/ -rgb2bw 0
```


Links to repositories on GitHub
---------------------------------
- [Kruziikrel13/ImageProcessing - Repository final state](https://github.com/Kruziikrel13/ImageProcessing)'
    - Implementation comparisons should be made against serial.cpp and parallel.cpp and the related image functions and their parallel overloads. As various non parallel related transformations were made to the original implementation in order to modernise it and ensure it adheres to the C++20 standards, as well as fixed a few bugs present in the original implementation.
    - Repository itself contains additional environment artefacts I used during development such as my NixOS shell configuration files.
- [iocentos/ImageProcessing](https://github.com/iocentos/ImageProcessing)
    - Original forked repository. Contains the original serial implementation before modernisations and refactorings along with own parallel implementations fully utilizing OpenMP and cilkPlus
