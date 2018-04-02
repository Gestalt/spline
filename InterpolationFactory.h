#ifndef InterpolationFactoryH
#define InterpolationFactoryH

#include <string>

class Interpolation;

class InterpolationFactory {
    public:
        static Interpolation* create(const std::string& type);
};

#endif
