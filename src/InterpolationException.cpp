#include "InterpolationException.h"

app::InterpolationException::InterpolationException(const std::string& reason_) throw()
    : reason(reason_) {
}

const char* app::InterpolationException::what() const throw() {
    return reason.c_str();
}
