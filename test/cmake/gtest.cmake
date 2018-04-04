if (WIN32)
        set(GTEST_MSVC_SEARCH MT)
endif(WIN32)

set(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/googletest)

find_package(GTest REQUIRED)
