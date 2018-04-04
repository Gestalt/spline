#include <exception>

#include "InterpolationFactory.h"
#include "NeighborInterpolation.h"
#include "LinearInterpolation.h"
#include "QuadricInterpolation.h"
#include "InterpolationException.h"

static sp::shared_ptr<Interpolation> createNeighbor() {
    return sp::make_shared<NeighborInterpolation>();
}

static sp::shared_ptr<Interpolation> createLinear() {
    return sp::make_shared<LinearInterpolation>();
}

static sp::shared_ptr<Interpolation> createQuadric() {
    return sp::make_shared<QuadricInterpolation>();
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

sp::shared_ptr<Interpolation> InterpolationFactory::create(const std::string& type) {
    std::map<std::string, InterpolationCreator>::const_iterator it = interpolations.find(type);

    if (it != interpolations.end()) {
        return it->second();
    }

    throw InterpolationException(
        "Attempt to create an unknown interpolation algorithm"
    );
}
