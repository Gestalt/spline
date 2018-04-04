if (WIN32)
        set(GMOCK_MSVC_SEARCH MT)
endif(WIN32)

set(GMOCK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/googlemock)

find_package(GMock REQUIRED)