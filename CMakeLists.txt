cmake_minimum_required (VERSION 2.8.11)


# set default build to debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Release or Debug" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall" CACHE INTERNAL "")

# defince cmake variables for file locations
file(GLOB USER_FILES 
"code/*.cpp"
)

# get folder name as project name
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

# create an executable for main.cpp in app folder
add_executable( run_app "app/main.cpp" ${USER_FILES})