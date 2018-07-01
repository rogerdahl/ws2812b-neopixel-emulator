cmake_minimum_required(VERSION 3.5)
project(emulator)

# If working with multiple sketches, select the one to build here
set(SKETCH arduino_sketch)

set(SKETCH_CPP "src/${SKETCH}.cpp")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Implicitly include Arduino.h in the sketch, as this is what the Arduino IDE
# does
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -include Arduino.h")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(
  src
)

link_libraries(
  m
  glut
  GL
  GLU
)

add_executable(
  emulator
  ${SKETCH_CPP}
  src/main.cpp
  src/NeoPixelEmulator.cpp
  src/Arduino.cpp
)

# Generate headers for sketch
add_custom_target(
  makeheaders
  COMMAND bin/makeheaders ${SKETCH_CPP}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Generating headers for sketch. sketch=${SKETCH_CPP} wd=${CMAKE_CURRENT_SOURCE_DIR}"
)

# Always generate headers for sketch before building emulator.
add_dependencies(emulator makeheaders)
