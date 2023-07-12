add_library(genesis_lib genesis.c functions.c)

# target_include_directories()

target_compile_features(genesis_lib SHARED c_std)