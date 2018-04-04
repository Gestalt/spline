#include "InterpolationFactory.h"
#include "NeighborInterpolation.h"
#include "LinearInterpolation.h"
#include "QuadricInterpolation.h"
#include "InterpolationException.h"

static sp::shared_ptr<app::Interpolation> createNeighbor() {
    return sp::make_shared<app::NeighborInterpolation>();
}

static sp::shared_ptr<app::Interpolation> createLinear() {
    return sp::make_shared<app::LinearInterpolation>();
}

static sp::shared_ptr<app::Interpolation> createQuadric() {
    return sp::make_shared<app::QuadricInterpolation>();
}

static bool registrar() {
    app::InterpolationFactory::instance()->registerInterpolation("Neighbor", createNeighbor);
    app::InterpolationFactory::instance()->registerInterpolation("Linear", createLinear);
    app::InterpolationFactory::instance()->registerInterpolation("Quadric", createQuadric);

    return true;
}

static bool reg = registrar();

app::InterpolationFactory::InterpolationFactory()
    : interpolations(std::map<std::string, InterpolationCreator>()) {
}

app::InterpolationFactory::~InterpolationFactory() {
    interpolations.clear();
}

app::InterpolationFactory* app::InterpolationFactory::instance() {
    static InterpolationFactory factory;
    return &factory;
}

bool app::InterpolationFactory::registerInterpolation(const std::string &type, InterpolationCreator creator) {
    std::pair<std::map<std::string, InterpolationCreator>::iterator, bool> res =
        interpolations.insert(std::make_pair(type, creator));

    return res.second;
}

sp::shared_ptr<app::Interpolation> app::InterpolationFactory::create(const std::string& type) {
    std::map<std::string, InterpolationCreator>::const_iterator it = interpolations.find(type);

    if (it != interpolations.end()) {
        return it->second();
    }

    throw InterpolationException(
        "Attempt to create an unknown interpolation algorithm"
    );
}
