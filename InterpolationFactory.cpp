#include <exception>

#include "InterpolationFactory.h"
#include "NeighborInterpolation.h"
#include "LinearInterpolation.h"
#include "QuadricInterpolation.h"
#include "InterpolationException.h"

static Interpolation* createNeighbor() {
    return new NeighborInterpolation();
}

static Interpolation* createLinear() {
    return new LinearInterpolation();
}

static Interpolation* createQuadric() {
    return new QuadricInterpolation();
}

static bool registrar() {
    InterpolationFactory::instance()->registerInterpolation("Neighbor", createNeighbor);
    InterpolationFactory::instance()->registerInterpolation("Linear", createLinear);
    InterpolationFactory::instance()->registerInterpolation("Quadric", createQuadric);

    return true;
}

static bool reg = registrar();

InterpolationFactory::InterpolationFactory()
    : interpolations(std::map<std::string, InterpolationCreator>()) {
}

InterpolationFactory::~InterpolationFactory() {
    interpolations.clear();
}

InterpolationFactory* InterpolationFactory::instance() {
    static InterpolationFactory factory;
    return &factory;
}

bool InterpolationFactory::registerInterpolation(const std::string &type, InterpolationCreator creator) {
    std::pair<std::map<std::string, InterpolationCreator>::iterator, bool> res =
        interpolations.insert(std::make_pair(type, creator));

    return res.second;
}

Interpolation* InterpolationFactory::create(const std::string& type) {
    std::map<std::string, InterpolationCreator>::const_iterator it = interpolations.find(type);

    if (it != interpolations.end()) {
        return it->second();
    }

    throw InterpolationException(
        "Attempt to create an unknown interpolation algorithm"
    );
}
