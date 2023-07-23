file(GLOB Sources *.c)
file(GLOB Headers *.h)

add_library(GenesisLib SHARED ${Sources} ${Headers})