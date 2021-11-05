cmake_minimum_required(VERSION 3.5)

SET(PROJECTNAME Jass)

project(${PROJECTNAME}
        VERSION 1.1.0)

set(CMAKE_CXX_STANDARD 11)  # enable C++11 standard


# Eigen library
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(${EIGEN3_INCLUDE_DIR})

# google test
add_subdirectory("extern/googletest" EXCLUDE_FROM_ALL)

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include_directories("${gtest_SOURCE_DIR}/include")

#
# pybind11
#
add_subdirectory("extern/pybind11")
include_directories("extern/pybind11/include")

set(PYTHONVERSION "3.7")
# None of the lines below works
add_definitions(-DPYBIND11_PYTHON_VERSION="${PYTHONVERSION}")
set(PYBIND11_PYTHON_VERSION ${PYTHONVERSION})

# add flags for release/debug build
set (CMAKE_CXX_FLAGS_RELEASE_INIT "-DNDEBUG")

#set (CMAKE_CXX_FLAGS "-fPIC -DPYBIND11_PYTHON_VERSION=3.8 -undefined dynamic_lookup")
set (CMAKE_CXX_FLAGS "-fPIC -DPYBIND11_PYTHON_VERSION=3.8")

# main source
set (MY_SOURCE_DIR "source")
include_directories(${MY_SOURCE_DIR}/include)
include_directories("/Users/toko/opt/anaconda3/include/python3.8")
link_directories("/Users/toko/opt/anaconda3/include/python3.8")

add_subdirectory(${MY_SOURCE_DIR})

# tests
#add_subdirectory(test)
