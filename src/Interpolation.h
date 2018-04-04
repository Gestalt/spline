#ifndef InterpolationH
#define InterpolationH

#include "Defs.h"

class TableBasedFunction;

class Interpolation {
    public:
        virtual ~Interpolation() {}
        virtual const float interpolate(const sp::shared_ptr<TableBasedFunction>& function, float argument) const = 0;
};

#endif

