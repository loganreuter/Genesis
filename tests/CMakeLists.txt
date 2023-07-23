cmake_minimum_required(VERSION 3.14)

project(
    Tests
    VERSION 0.1
    DESCRIPTION "Testing for genesis"
    LANGUAGES C
)

file(GLOB Sources *.c)
file(GLOB Headers *.h)

file(GLOB LIB_SOURCES ../src/*.c)
file(GLOB LIB_HEADERS ../src/*.h)

add_library(GenesisLib ${LIB_SOURCES} ${LIB_HEADERS})

add_executable(test ${Sources} ${Headers})

target_link_libraries(test PUBLIC GenesisLib)