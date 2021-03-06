cmake_minimum_required(VERSION 3.0.2)
project(spline)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

option(USE_BOOST "Using <boost> to access c++11 features" OFF)

add_executable(${PROJECT_NAME}
	main.cpp
	src/Point.cpp
	src/Spline.cpp
	src/InterpolationFactory.cpp
	src/LinearInterpolation.cpp
	src/NeighborInterpolation.cpp
	src/QuadricInterpolation.cpp
	src/TableBasedFunction.cpp
	src/LagrangePolynom.cpp
	src/Parameters.cpp
	src/InputFile.cpp
	src/OutputFile.cpp
	src/Application.cpp
	src/InterpolationException.cpp
	src/Log.cpp
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
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
)