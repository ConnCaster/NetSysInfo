set(PROJECT_NAME Server)

list(APPEND ${PROJECT_NAME}_SOURCES
        server_main.cpp
        server.cpp
        action.cpp
        connection.cpp
        ${CMAKE_SOURCE_DIR}/sources/fileHandler/file_handler.cpp
)

add_executable(start_server ${${PROJECT_NAME}_SOURCES} )

target_include_directories(start_server PUBLIC "${CMAKE_SOURCE_DIR}/lib/JSON/include"
                                                "${CMAKE_SOURCE_DIR}/include/"
                                                "${CMAKE_SOURCE_DIR}/include/server"
                                                "${CMAKE_SOURCE_DIR}/include/fileHandler"
                                                "${CMAKE_SOURCE_DIR}/include/userManager"
)