cmake_minimum_required(VERSION 3.10)
project(FoSolver)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -g")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/header
                    ${CMAKE_SOURCE_DIR}/algo
                    ${CMAKE_SOURCE_DIR}/algo/PSO
                    ${CMAKE_SOURCE_DIR}/algo/GA
                    ${CMAKE_SOURCE_DIR}/algo/ABC
                    ${CMAKE_SOURCE_DIR}/algo/GWO
                    ${CMAKE_SOURCE_DIR}/algo/WOA
                    ${CMAKE_SOURCE_DIR}/utils
                    /usr/local/include)

# Source files
set(MAIN_SRC ${CMAKE_SOURCE_DIR}/main.cpp)
set(FUNC_SRC ${CMAKE_SOURCE_DIR}/benchmark.cpp)
set(ALGO_SRC ${CMAKE_SOURCE_DIR}/algo/algo.cpp
             ${CMAKE_SOURCE_DIR}/algo/PSO/pso.cpp
             ${CMAKE_SOURCE_DIR}/algo/GA/ga.cpp
             ${CMAKE_SOURCE_DIR}/algo/ABC/abc.cpp
             ${CMAKE_SOURCE_DIR}/algo/GWO/gwo.cpp
             ${CMAKE_SOURCE_DIR}/algo/WOA/woa.cpp)
set(UTILS_SRC ${CMAKE_SOURCE_DIR}/utils/utils.cpp)

# Output directories
set(BIN_DIR ${CMAKE_SOURCE_DIR}/cmd)

# Target for the main solver
add_executable(fo_solver ${MAIN_SRC} ${ALGO_SRC} ${UTILS_SRC})

# Target for the benchmark
add_executable(benchmark ${FUNC_SRC} ${UTILS_SRC})

# Link the yaml-cpp library
target_link_libraries(fo_solver /usr/local/lib/libyaml-cpp.a)
target_link_libraries(benchmark /usr/local/lib/libyaml-cpp.a)

# Set output directories
set_target_properties(fo_solver PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set_target_properties(benchmark PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Clean
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -P cmake_clean.cmake
    COMMENT "Cleaning up the project"
)
