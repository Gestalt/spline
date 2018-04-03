cmake_minimum_required(VERSION 3.0.2)
project(spline)

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
)

target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src.txt ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dest.txt ${CMAKE_CURRENT_BINARY_DIR}
)