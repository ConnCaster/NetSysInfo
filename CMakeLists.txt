cmake_minimum_required(VERSION 3.28)

project(Client-Server)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(sources/client)
add_subdirectory(sources/server)

#Библиотеки
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/SQLiteCpp")

target_link_libraries(start_admin SQLiteCpp
        sqlite3
        pthread
        dl)

