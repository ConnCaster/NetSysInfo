add_executable(start_server server.cpp
        ${CMAKE_SOURCE_DIR}/include/server/server.h)

target_include_directories(start_server PUBLIC "${CMAKE_SOURCE_DIR}/lib/JSON/include"
                                                "${CMAKE_SOURCE_DIR}/include/server"
                                                 "${CMAKE_SOURCE_DIR}/include/database"
                                                    "${CMAKE_SOURCE_DIR}/include/userManager")