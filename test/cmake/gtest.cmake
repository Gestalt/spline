if (WIN32)
        set(GTEST_MSVC_SEARCH MT)
endif(WIN32)

set(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest)

find_package(GTest REQUIRED)
