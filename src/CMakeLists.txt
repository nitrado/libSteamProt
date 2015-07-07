SET(SOURCES
    libSteamProt.h 
	libSteamProt.c
	crc.c
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSP_COMPRESSED=1")

add_library(libSteamProt STATIC ${SOURCES})

target_link_libraries(libSteamProt bzlib)

install(TARGETS libSteamProt DESTINATION lib)