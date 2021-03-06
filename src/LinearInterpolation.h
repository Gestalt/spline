#ifndef LinearInterpolationH
#define LinearInterpolationH

#include "Interpolation.h"

namespace app {

class LinearInterpolation : public Interpolation {
    public:
        const float interpolate(const sp::shared_ptr<TableBasedFunction>& function, float argument) const;
};

}
#endif

