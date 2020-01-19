cmake_minimum_required(VERSION 3.7)
project(171044086_Hamza_YOĞURTCUOĞLU)

# CMake can set the standard in a cross-platform way for you
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES main.cpp SubTimer.cpp TimerEntity.cpp)
add_executable(exe ${SOURCE_FILES})

# These two lines add the platform-specific magic for the right threading library/headers.
find_package(Threads)
target_link_libraries(exe Threads::Threads)