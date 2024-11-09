set(PROJECT_NAME Client)

list(APPEND ${PROJECT_NAME}_SOURCES
        client_main.cpp
        client.cpp
        cli_connection.cpp
)

add_executable(start_client ${${PROJECT_NAME}_SOURCES})

target_include_directories(start_client PUBLIC "${CMAKE_SOURCE_DIR}/lib/JSON/include"
                                                "${CMAKE_SOURCE_DIR}/include/client"
                                                "${CMAKE_SOURCE_DIR}/include/")
