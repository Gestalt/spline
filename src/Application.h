#ifndef ApplicationH
#define ApplicationH

namespace app {

class Parameters;

class Application {
    public:
        static void process(const Parameters& params);
};

}
#endif

