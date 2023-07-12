cmake_minimum_required(VERSION 3.14)

project(
    Tests
    VERSION 1.0
    DESCRIPTION "Testing for genesis"
    LANGUAGES C
)


add_library(GenesisLib ../src/genesis.c ../src/functions.c)

add_executable(test tests.c helper.c)

target_link_libraries(test PUBLIC GenesisLib)
