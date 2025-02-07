set(PROJECT_NAME Server)

# Реализация сервера
list(APPEND ${PROJECT_NAME}_SOURCES
        server_main.cpp
        server.cpp
        serv_connection.cpp
        adm_menu/menu.cpp
        ${CMAKE_SOURCE_DIR}/sources/fileHandler/file_handler.cpp
        actions/registration.cpp
        ${CMAKE_SOURCE_DIR}/sources/utils/utils.cpp
)

# Реализация новых executors
list(APPEND ${PROJECT_NAME}_SOURCES)


add_executable(start_server ${${PROJECT_NAME}_SOURCES})

target_include_directories(start_server PUBLIC "${CMAKE_SOURCE_DIR}/lib/JSON/include"
        "${CMAKE_SOURCE_DIR}/include/utils"
        "${CMAKE_SOURCE_DIR}/include/server"
        "${CMAKE_SOURCE_DIR}/include/server/adm_menu"
        "${CMAKE_SOURCE_DIR}/include/fileHandler"
        "${CMAKE_SOURCE_DIR}/include/userManager"
)

add_subdirectory(adm_menu)