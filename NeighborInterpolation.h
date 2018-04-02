#ifndef NeighborInterpolationH
#define NeighborInterpolationH

#include "Interpolation.h"

class NeighborInterpolation : public Interpolation {
    public:
        const float interpolate(TableBasedFunction* function, float argument) const;
};

#endif
