#ifndef SplineH
#define SplineH

#include "Defs.h"

namespace app {

class Interpolation;
class TableBasedFunction;

class Spline {
    public:
        explicit Spline(sp::shared_ptr<Interpolation>);

        const float interpolate(const sp::shared_ptr<TableBasedFunction>& function, float argument) const;
    private:
        sp::shared_ptr<Interpolation> interpolation;

};

}
#endif

