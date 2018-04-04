cmake_minimum_required(VERSION 3.0.2)
project(spline_test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

option(USE_BOOST "Using <boost> to access c++11 features" OFF)

include(gtest)
include(gmock)

enable_testing()

add_executable(${PROJECT_NAME}
	main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/Point.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/InterpolationFactory.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/NeighborInterpolation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/LinearInterpolation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/QuadricInterpolation.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/TableBasedFunction.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/LagrangePolynom.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../src/InterpolationException.cpp
)

if(USE_BOOST)
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE USE_BOOST
	)
	find_package(Boost REQUIRED)

	target_include_directories(${PROJECT_NAME}
		PRIVATE	${Boost_INCLUDE_DIRS}
			${Boost_INCLUDE_DIRS}/boost
	)
endif(USE_BOOST)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/../src
		${GTEST_INCLUDE_DIRS}
		${GMOCK_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE ${GTEST_LIBRARIES}
                ${GTEST_MAIN_LIBRARIES}
		${GMOCK_LIBRARIES}
                ${GMOCK_MAIN_LIBRARIES}
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
