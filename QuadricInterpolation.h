#ifndef QuadricInterpolationH
#define QuadricInterpolationH

#include "Interpolation.h"

class QuadricInterpolation : public Interpolation {
    public:
        const float interpolate(TableBasedFunction* function, float argument) const;
};

#endif
