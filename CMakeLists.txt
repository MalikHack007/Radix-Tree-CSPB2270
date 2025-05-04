cmake_minimum_required (VERSION 3.22)


# set default build to debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Release or Debug" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall" CACHE INTERNAL "")

# Set C++17 as the required standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Radix-Tree")

#find the external libraries
find_package(jsoncpp CONFIG REQUIRED)

# create an executable for main.cpp in app folder
add_executable(run_app
  "app/main.cpp"
  "code/radix_tree.cpp")

# define a preprocessor macro
target_compile_definitions(run_app PRIVATE
    FILE_PATH="${CMAKE_SOURCE_DIR}/Files"
)

# Use the correct target from jsoncpp
target_link_libraries(run_app PRIVATE JsonCpp::JsonCpp) #use jsoncpp_lib for Visual Studio IDE

target_include_directories(
  run_app
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/code
) #look for header files in code folder
