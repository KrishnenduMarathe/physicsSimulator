cmake_minimum_required(VERSION 3.22)
project(physicsSimulator VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

add_executable(physicsSimulator src/main.cpp src/main.h src/map.h src/PhysicsEngine.cpp src/PhysicsEngine.h src/PhysicsObject.h src/pixel.h src/std_libs.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(physicsSimulator PRIVATE Threads::Threads)
