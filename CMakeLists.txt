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

include_directories(
    include
    tests/include
)

# add_executable(
#   ${PROJECT_NAME}
#   src/main.cpp
# )

enable_testing()

add_executable(
  tests
  tests/canvas_test.cpp
  tests/cartesia_test.cpp
  tests/colors_test.cpp
  tests/matrices_test.cpp
  src/matrices.cpp
)
target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)