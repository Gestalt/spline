#ifndef NeighborInterpolationH
#define NeighborInterpolationH

#include "Interpolation.h"

class NeighborInterpolation : public Interpolation {
    public:
        const float interpolate(const sp::shared_ptr<TableBasedFunction>& function, float argument) const;
};

#endif

