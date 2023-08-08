cmake_minimum_required(VERSION 3.14)
project(RayTracer)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_FLAGS "-pg")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

# add threading
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(
  main
)
target_sources(
  main
  PUBLIC src/raytracer.cpp
  PRIVATE src/raytracer/core/matrices/helper.cpp
  PRIVATE src/raytracer/core/matrices/matrix.cpp
  PRIVATE src/raytracer/core/matrices/transformations.cpp
)
target_link_libraries(main PRIVATE Threads::Threads)
target_include_directories(
  main
  PRIVATE src
)

enable_testing()

add_executable(
  tests
)
target_sources(
  tests
  PRIVATE tests/camera.test.cpp
  PRIVATE tests/canvas.test.cpp
  PRIVATE tests/colors.test.cpp
  PRIVATE tests/light.test.cpp
  PRIVATE tests/intersections.test.cpp
  PRIVATE tests/material.test.cpp
  PRIVATE tests/matrix.test.cpp
  PRIVATE tests/rays.test.cpp
  PRIVATE tests/pattern.test.cpp
  PRIVATE tests/plane.test.cpp
  PRIVATE tests/shape.test.cpp
  PRIVATE tests/sphere.test.cpp
  PRIVATE tests/transformable.test.cpp
  PRIVATE tests/transformations.test.cpp
  PRIVATE tests/world.test.cpp
  PRIVATE src/raytracer/core/matrices/helper.cpp
  PRIVATE src/raytracer/core/matrices/matrix.cpp
  PRIVATE src/raytracer/core/matrices/transformations.cpp
)
target_link_libraries(
  tests
  GTest::gtest_main
  Threads::Threads
)
target_include_directories(
  tests
  PRIVATE src
  PRIVATE tests/include
)

include(GoogleTest)
gtest_discover_tests(tests)