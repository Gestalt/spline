cmake_minimum_required(VERSION 3.0.2)
project(spline_test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(gtest)
include(gmock)

enable_testing()

add_executable(${PROJECT_NAME}
	main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../Point.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../InterpolationFactory.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../NeighborInterpolation.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../LinearInterpolation.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../QuadricInterpolation.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../TableBasedFunction.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../LagrangePolynom.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../InterpolationException.cpp
)

#if(USE_BOOST)
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE USE_BOOST
	)
	find_package(Boost REQUIRED)

	target_include_directories(${PROJECT_NAME}
		PUBLIC	${Boost_INCLUDE_DIRS}
			${Boost_INCLUDE_DIRS}/boost
	)
#endif(USE_BOOST)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/..
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
