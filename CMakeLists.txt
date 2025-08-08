cmake_minimum_required(VERSION 3.5)
set( CMAKE_CXX_COMPILER "D:/DXLIB/x86_64-13.1.0-release-posix-seh-msvcrt-rt_v11-rev1/mingw64/bin/g++.exe" )

project(DXLIB CXX)
set(LIBRARY_SOURCES 
${CMAKE_SOURCE_DIR}/lib/libDxLib.a
${CMAKE_SOURCE_DIR}/lib/libDxUseCLib.a
${CMAKE_SOURCE_DIR}/lib/libDxDrawFunc.a
${CMAKE_SOURCE_DIR}/lib/libjpeg.a
${CMAKE_SOURCE_DIR}/lib/libpng.a
${CMAKE_SOURCE_DIR}/lib/libzlib.a
${CMAKE_SOURCE_DIR}/lib/libtiff.a
${CMAKE_SOURCE_DIR}/lib/libtheora_static.a
${CMAKE_SOURCE_DIR}/lib/libvorbis_static.a
${CMAKE_SOURCE_DIR}/lib/libvorbisfile_static.a
${CMAKE_SOURCE_DIR}/lib/libogg_static.a
${CMAKE_SOURCE_DIR}/lib/libbulletdynamics.a
${CMAKE_SOURCE_DIR}/lib/libbulletcollision.a
${CMAKE_SOURCE_DIR}/lib/libbulletmath.a
${CMAKE_SOURCE_DIR}/lib/libopusfile.a
${CMAKE_SOURCE_DIR}/lib/libopus.a
${CMAKE_SOURCE_DIR}/lib/libsilk_common.a
${CMAKE_SOURCE_DIR}/lib/libcelt.a
)
#file(GLOB LIBRARY_SOURCES "${CMAKE_SOURCE_DIR}/lib/*.a")
#message("Detected source files: ${LIBRARY_SOURCES}")
#add_library(library STATIC ${LIBRARY_SOURCES}) cppから.aファイルに

add_executable(main 
${CMAKE_SOURCE_DIR}/src/main.cpp
${CMAKE_SOURCE_DIR}/src/Manager.cpp
${CMAKE_SOURCE_DIR}/src/VECTOR.cpp
${CMAKE_SOURCE_DIR}/src/Start/Start.cpp
${CMAKE_SOURCE_DIR}/src/Select/Select.cpp
${CMAKE_SOURCE_DIR}/src/Othello/3DOthello.cpp
${CMAKE_SOURCE_DIR}/src/Othello/OthelloBoard.cpp)

target_link_libraries(main ${LIBRARY_SOURCES})
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include/)