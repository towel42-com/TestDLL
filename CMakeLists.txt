# The MIT License (MIT)
#
# Copyright (c) 2020-2021 Scott Aron Bloom
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.1)
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

project(TestDLL-Top) 

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/SABUtils/Modules ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
find_package(Threads)
find_package(Qt5 COMPONENTS Core Xml REQUIRED)
find_package(Deploy REQUIRED)
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

SET( CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/Install )

add_subdirectory( StubbedSharedLibrary )
add_subdirectory( ProperSharedLibrary )
add_subdirectory( MainLib )
add_subdirectory( cli )

SET( CPACK_PACKAGE_VENDOR "Scott Aron Bloom" )
SET( CPACK_PACKAGE_VERSION_MAJOR "0" )
SET( CPACK_PACKAGE_VERSION_MINOR "1" )
SET( CPACK_PACKAGE_VERSION_PATCH "0" )
set( CPACK_NSIS_EXECUTABLES_DIRECTORY ".")

set( CPACK_NSIS_MODIFY_PATH OFF)
SET( CPACK_GENERATOR NSIS ZIP )
include( CPack )
