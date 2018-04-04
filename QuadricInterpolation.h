#ifndef QuadricInterpolationH
#define QuadricInterpolationH

#include "Interpolation.h"

class QuadricInterpolation : public Interpolation {
    public:
        const float interpolate(const sp::shared_ptr<TableBasedFunction>& function, float argument) const;
};

#endif
