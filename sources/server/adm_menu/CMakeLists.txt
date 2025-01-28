set(PROJECT_NAME Admin)

# Реализация сервера
list(APPEND ${PROJECT_NAME}_SOURCES
        menu.cpp
        requests.cpp
        ${CMAKE_SOURCE_DIR}/sources/utils.cpp
        ${CMAKE_SOURCE_DIR}/sources/server/server.cpp
        ${CMAKE_SOURCE_DIR}/sources/server/serv_connection.cpp
        ${CMAKE_SOURCE_DIR}/sources/fileHandler/file_handler.cpp
        ${CMAKE_SOURCE_DIR}/sources/server/actions/registration.cpp
)

# Реализация новых executors
list(APPEND ${PROJECT_NAME}_SOURCES)

add_executable(start_admin ${${PROJECT_NAME}_SOURCES})

target_include_directories(start_admin PUBLIC "${CMAKE_SOURCE_DIR}/include/"
                                            "${CMAKE_SOURCE_DIR}/include/server"
                                            "${CMAKE_SOURCE_DIR}/lib/JSON/include"
                                            "${CMAKE_SOURCE_DIR}/include/fileHandler"
                                            "${CMAKE_SOURCE_DIR}/include/userManager"
                                            "${CMAKE_SOURCE_DIR}/include/server/adm_menu"

)
