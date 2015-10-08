SET(SOURCES
    main.cpp
)

add_executable(rconserver ${SOURCES})
set_target_properties(rconserver PROPERTIES OUTPUT_NAME rconserver)

target_link_libraries(rconserver libSteamProt)