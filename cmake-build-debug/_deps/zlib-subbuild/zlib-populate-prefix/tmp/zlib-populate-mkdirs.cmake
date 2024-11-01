# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/zlib-src"
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/zlib-build"
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/zlib-subbuild/zlib-populate-prefix"
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/zlib-subbuild/zlib-populate-prefix/tmp"
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp"
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/zlib-subbuild/zlib-populate-prefix/src"
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
