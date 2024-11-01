# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/cpr-src"
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/cpr-build"
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/cpr-subbuild/cpr-populate-prefix"
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/cpr-subbuild/cpr-populate-prefix/tmp"
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp"
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/cpr-subbuild/cpr-populate-prefix/src"
  "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/bgd/Desktop/sfml-template/cmake-build-debug/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
