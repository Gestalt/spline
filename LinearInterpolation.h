#ifndef LinearInterpolationH
#define LinearInterpolationH

#include "Interpolation.h"

class LinearInterpolation : public Interpolation {
    public:
        const float interpolate(TableBasedFunction* function, float argument) const;
};

#endif
