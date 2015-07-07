SET(SOURCES
    blocksort.c
	bzlib.c
	bzlib.h
	bzlib_private.h
	compress.c
	crctable.c
	decompress.c
	huffman.c
	libbz2.def
	randtable.c
)

add_library(bzlib STATIC ${SOURCES})

install(TARGETS bzlib DESTINATION lib)