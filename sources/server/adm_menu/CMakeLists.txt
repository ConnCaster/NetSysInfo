set(PROJECT_NAME Admin)
# Реализация вспомогательных средств
list(APPEND ${PROJECT_NAME}_SOURCES_EXTRA
        ${CMAKE_SOURCE_DIR}/sources/log/logger.cpp
        ${CMAKE_SOURCE_DIR}/sources/utils/utils.cpp
)
# Реализация сервера
list(APPEND ${PROJECT_NAME}_SOURCES_SERVER
        ${CMAKE_SOURCE_DIR}/sources/server/server.cpp
        ${CMAKE_SOURCE_DIR}/sources/server/serv_connection.cpp
        ${CMAKE_SOURCE_DIR}/sources/server/s_request_handler.cpp
        ${CMAKE_SOURCE_DIR}/sources/server/actions/member_info.cpp
        ${CMAKE_SOURCE_DIR}/sources/server/actions/registration.cpp
)
# Реализация меню администратора
list(APPEND ${PROJECT_NAME}_SOURCES_ADMIN_MENU
        menu.cpp
        users/users.cpp
        users/admin_actions_on_users.cpp
        turn_on.cpp
        turn_off.cpp
        requests.cpp
)
# Реализация базы данных
list(APPEND ${PROJECT_NAME}_SOURCES_STORAGE
        ${CMAKE_SOURCE_DIR}/sources/storage/file_database/file_database.cpp
        ${CMAKE_SOURCE_DIR}/sources/storage/sql_database/requests/insert.cpp
        ${CMAKE_SOURCE_DIR}/sources/storage/sql_database/requests/select.cpp


)

add_executable(start_admin ${${PROJECT_NAME}_SOURCES_SERVER}
                            ${${PROJECT_NAME}_SOURCES_ADMIN_MENU}
                            ${${PROJECT_NAME}_SOURCES_STORAGE}
                            ${${PROJECT_NAME}_SOURCES_EXTRA}
        )

# Инклуды
target_include_directories(start_admin PUBLIC   "${CMAKE_SOURCE_DIR}/include/log"
                                                "${CMAKE_SOURCE_DIR}/include/utils"
                                                "${CMAKE_SOURCE_DIR}/include/server"
                                                "${CMAKE_SOURCE_DIR}/include/storage"
                                                "${CMAKE_SOURCE_DIR}/include/userManager"
                                                "${CMAKE_SOURCE_DIR}/include/server/adm_menu"
                                                "${CMAKE_SOURCE_DIR}/include/storage/interfaces"
                                                "${CMAKE_SOURCE_DIR}/include/storage/sql_requests"

)
# Библиотеки
target_include_directories(start_admin PUBLIC "${CMAKE_SOURCE_DIR}/lib/JSON/include")

