cmake_minimum_required(VERSION 3.0.2)
project(spline_test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(gtest)
include(gmock)

enable_testing()

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
	PRIVATE ${GTEST_INCLUDE_DIRS}
		${GMOCK_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE ${GTEST_LIBRARIES}
                ${GTEST_MAIN_LIBRARIES}
		${GMOCK_LIBRARIES}
                ${GMOCK_MAIN_LIBRARIES}
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
