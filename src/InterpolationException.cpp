#include "InterpolationException.h"

InterpolationException::InterpolationException(const std::string& reason_) throw()
    : reason(reason_) {
}

const char* InterpolationException::what() const throw() {
    return reason.c_str();
}
