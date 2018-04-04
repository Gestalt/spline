#ifndef NeighborInterpolationH
#define NeighborInterpolationH

#include "Interpolation.h"

namespace app {

class NeighborInterpolation : public Interpolation {
    public:
        const float interpolate(const sp::shared_ptr<TableBasedFunction>& function, float argument) const;
};

}
#endif

