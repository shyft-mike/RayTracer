cmake_minimum_required(VERSION 3.14)
project(RayTracer)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(
  main
)
target_sources(
  main
  PUBLIC src/main.cpp
  PRIVATE src/shapes/shapes.cpp
  PRIVATE src/shapes/spheres.cpp
  PRIVATE src/matrices/helper.cpp
  PRIVATE src/matrices/matrices.cpp
  PRIVATE src/matrices/transformations.cpp
)
target_include_directories(
  main
  PRIVATE include
)

enable_testing()

add_executable(
  tests
)
target_sources(
  tests
  PRIVATE tests/canvas_test.cpp
  PRIVATE tests/cartesia_test.cpp
  PRIVATE tests/colors_test.cpp
  PRIVATE tests/matrices_test.cpp
  PRIVATE tests/intersections_test.cpp
  PRIVATE tests/rays_test.cpp
  PRIVATE tests/spheres_test.cpp
  PRIVATE tests/transformations_test.cpp
  PRIVATE src/matrices/helper.cpp
  PRIVATE src/matrices/matrices.cpp
  PRIVATE src/matrices/transformations.cpp
  PRIVATE src/shapes/shapes.cpp
)
target_link_libraries(
  tests
  GTest::gtest_main
)
target_include_directories(
  tests
  PRIVATE include
  PRIVATE tests/include
)

include(GoogleTest)
gtest_discover_tests(tests)