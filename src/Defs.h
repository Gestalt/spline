#ifndef DefsH
#define DefsH

#ifdef USE_BOOST
    #include <boost/shared_ptr.hpp>
    #include <boost/make_shared.hpp>
#else
    #include <memory>
#endif
    
#ifdef USE_BOOST
    namespace sp = boost;
#else
    namespace sp = std;
#endif

#endif

