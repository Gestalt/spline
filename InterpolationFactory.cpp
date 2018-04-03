#include <exception>

#include "InterpolationFactory.h"
#include "NeighborInterpolation.h"
#include "LinearInterpolation.h"
#include "QuadricInterpolation.h"
#include "InterpolationException.h"

Interpolation* InterpolationFactory::create(const std::string& type) {
    if (type == std::string("Neighbor")) {
        return new NeighborInterpolation();
    }

    if (type == std::string("Linear")) {
        return new LinearInterpolation();
    }

    if (type == std::string("Quadric")) {
        return new QuadricInterpolation();
    }

    throw InterpolationException(
        "Attempt to create an unknown interpolation algorithm"
    );
}
