cmake_minimum_required(VERSION 3.0.2)
project(spline)

add_executable(${PROJECT_NAME} main.cpp)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}
)