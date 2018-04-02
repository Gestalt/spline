#include "Spline.h"
#include "Interpolation.h"

Spline::Spline(Interpolation* interpolation_)
    : interpolation(interpolation_) {
}

Spline::~Spline() {
    delete interpolation;
}

const float Spline::interpolate(TableBasedFunction* function, float argument) const {
    if (interpolation && function) {
        return interpolation->interpolate(function, argument);
    }
    return 0.f;
}
