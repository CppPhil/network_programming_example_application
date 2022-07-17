# CMakeList.txt : CMake project for network_programming, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("network_programming")

# Add source to this project's executable.
add_executable (network_programming "network_programming.cpp" "network_programming.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET network_programming PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
