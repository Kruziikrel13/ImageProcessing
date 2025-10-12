#pragma once

#include <exception>
#include <new>
#include <stdexcept>

namespace IMAGE {

    /*classes to use as exception objects */

    class BadAlloc : public std::runtime_error {
      public:
        explicit BadAlloc(const std::string& arg = "") : std::runtime_error(arg) {}
    };

    class ImageFormatError : public std::logic_error {
      public:
        explicit ImageFormatError(const std::string& arg = "") : std::logic_error(arg) {}
    };

    class NotSupportedFormat : public std::runtime_error {
      public:
        explicit NotSupportedFormat(const std::string& arg = "") : std::runtime_error(arg) {}
    };

    class InvalidArgument : public std::invalid_argument {
      public:
        explicit InvalidArgument(const std::string& arg = "") : std::invalid_argument(arg) {}
    };

    class FileIoFailed : public std::runtime_error {
      public:
        explicit FileIoFailed(const std::string& arg = "") : std::runtime_error(arg) {}
    };

    class EmptyRaster : public std::logic_error {
      public:
        explicit EmptyRaster(const std::string& arg = "") : std::logic_error(arg) {}
    };

    class EmptyImage : public std::logic_error {
      public:
        explicit EmptyImage(const std::string& arg = "") : std::logic_error(arg) {}
    };

} // end of namespace IMAGE
