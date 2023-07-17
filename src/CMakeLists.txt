add_library(genesis_lib genesis.c functions.c)

# target_include_directories()

target_compile_features(genesis_lib INTERFACE CMAKE_C_COMPILE_FEATURES)