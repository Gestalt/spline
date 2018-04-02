#ifndef SplineH
#define SplineH

class Interpolation;
class TableBasedFunction;

class Spline {
    public:
        explicit Spline(Interpolation*);
        ~Spline();

        const float interpolate(TableBasedFunction* function, float argument) const;
    private:
        Interpolation* interpolation;

};

#endif
