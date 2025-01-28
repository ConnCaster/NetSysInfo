set(PROJECT_NAME Client)

list(APPEND ${PROJECT_NAME}_SOURCES
        client.cpp
        client_main.cpp
        cli_connection.cpp
        ${CMAKE_SOURCE_DIR}/sources/utils/utils.cpp
)

add_executable(start_client ${${PROJECT_NAME}_SOURCES})

target_include_directories(start_client PUBLIC  "${CMAKE_SOURCE_DIR}/include/utils/"
                                                "${CMAKE_SOURCE_DIR}/include/client"
                                                "${CMAKE_SOURCE_DIR}/lib/JSON/include"
)
