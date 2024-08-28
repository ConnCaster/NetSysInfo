add_executable(start_server server.cpp
        include/server.h)

target_include_directories(start_server PUBLIC "${CMAKE_SOURCE_DIR}/lib/include"
                                                "./include")