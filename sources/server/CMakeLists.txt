add_executable(start_server server.cpp
        ../../include/server/server.h)

target_include_directories(start_server PUBLIC "${CMAKE_SOURCE_DIR}/lib/JSON/include"
                                                "${CMAKE_SOURCE_DIR}/include/server")