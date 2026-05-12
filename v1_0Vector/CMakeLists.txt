cmake_minimum_required(VERSION 3.14)
project(Studentas)

set(CMAKE_CXX_STANDARD 14)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

add_executable(programa
    failai.cpp
    generatorius.cpp
    ivedimas.cpp
    mediana.cpp
    output.cpp
    rusiavimas.cpp
    studentai.cpp
    tyrimai.cpp
    v1_0.cpp
)

add_executable(testai
    testai.cpp
    studentai.cpp
    mediana.cpp
)
target_link_libraries(testai gtest_main)