#include "Spline.h"
#include "Interpolation.h"

app::Spline::Spline(sp::shared_ptr<Interpolation> interpolation_)
    : interpolation(interpolation_) {
}

const float app::Spline::interpolate(const sp::shared_ptr<TableBasedFunction>& function, float argument) const {
    if (interpolation && function) {
        return interpolation->interpolate(function, argument);
    }
    return 0.f;
}
