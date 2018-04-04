cmake_minimum_required(VERSION 3.0.2)
project(spline)

option(USE_BOOST "Using <boost> to access c++11 features" OFF)

add_executable(${PROJECT_NAME}
	main.cpp
	Point.cpp
	Spline.cpp
	InterpolationFactory.cpp
	LinearInterpolation.cpp
	NeighborInterpolation.cpp
	QuadricInterpolation.cpp
	TableBasedFunction.cpp
	LagrangePolynom.cpp
	Parameters.cpp
	InputFile.cpp
	OutputFile.cpp
	Application.cpp
	InterpolationException.cpp
	Log.cpp
)

if(USE_BOOST)
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE USE_BOOST
	)
	find_package(Boost REQUIRED)

	target_include_directories(${PROJECT_NAME}
		PUBLIC	${Boost_INCLUDE_DIRS}
			${Boost_INCLUDE_DIRS}/boost
	)
endif(USE_BOOST)

target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src.txt ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dest.txt ${CMAKE_CURRENT_BINARY_DIR}
)