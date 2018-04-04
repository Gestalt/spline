#ifndef InterpolationFactoryH
#define InterpolationFactoryH

#include "Defs.h"
#include <string>
#include <map>

class Interpolation;
class InterpolationFactory;

typedef sp::shared_ptr<Interpolation> (*InterpolationCreator)();

class InterpolationFactory {
    public:
        ~InterpolationFactory();
        static InterpolationFactory* instance();
        sp::shared_ptr<Interpolation> create(const std::string& type);
        bool registerInterpolation(const std::string &type, InterpolationCreator creator);
    private:
        InterpolationFactory();
        InterpolationFactory(const InterpolationFactory&);
        InterpolationFactory& operator=(const InterpolationFactory&);
    private:
        std::map<std::string, InterpolationCreator> interpolations;
};

#endif

