add_executable(start_menu menu.cpp)

target_include_directories(start_menu PUBLIC "${CMAKE_SOURCE_DIR}/include/server/adm_menu"
        "${CMAKE_SOURCE_DIR}/include/"
        "${CMAKE_SOURCE_DIR}/include/server"
        "${CMAKE_SOURCE_DIR}/include/server/adm_menu"
        "${CMAKE_SOURCE_DIR}/include/fileHandler"
        "${CMAKE_SOURCE_DIR}/include/userManager"
        "${CMAKE_SOURCE_DIR}/lib/JSON/include"
)
