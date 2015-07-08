SET(SOURCES
    main.cpp
)

add_executable(queryserver ${SOURCES})
set_target_properties(queryserver PROPERTIES OUTPUT_NAME queryserver)

target_link_libraries(queryserver libSteamProt)