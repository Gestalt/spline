#ifndef InterpolationH
#define InterpolationH

class TableBasedFunction;

class Interpolation {
    public:
        virtual ~Interpolation() {}
        virtual const float interpolate(TableBasedFunction* function, float argument) const = 0;
};

#endif
