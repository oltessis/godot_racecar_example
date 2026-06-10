cmake_minimum_required(VERSION 3.20)
project(vehicle_bridge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# -----------------------
# Core Logic Library
# -----------------------
add_library(racecar_core STATIC
    src/core/ppm_encoder.cpp
)

target_include_directories(racecar_core PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/fpga_racecar_verilog/obj_dir
    /usr/share/verilator/include
)

# -----------------------
# Verilator sources
# -----------------------
file(GLOB VERILATOR_SOURCES
    fpga_racecar_verilog/obj_dir/*.cpp
)

set(VERILATOR_RUNTIME
    /usr/share/verilator/include/verilated.cpp
    /usr/share/verilator/include/verilated_threads.cpp
)

# -----------------------
# Create shared library for Godot
# -----------------------
set(SOURCES
    vehicle_bridge.cpp
    register_types.cpp
)

add_library(vehicle_bridge SHARED
    ${SOURCES}
    ${VERILATOR_SOURCES}
    ${VERILATOR_RUNTIME}
)

target_link_libraries(vehicle_bridge PRIVATE
    racecar_core
    ${CMAKE_SOURCE_DIR}/godot-cpp/bin/libgodot-cpp.linux.template_debug.x86_64.a
)

target_include_directories(vehicle_bridge PRIVATE
    godot-cpp/include
    godot-cpp/gen/include
)

# -----------------------
# Unit Testing (GTest)
# -----------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Forcing GTest to use shared runtime on Windows if needed, 
# but we are on Linux.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests 
    tests/test_simulation.cpp
    ${VERILATOR_SOURCES}
    ${VERILATOR_RUNTIME}
)

target_link_libraries(run_tests 
    GTest::gtest_main
    racecar_core
)
