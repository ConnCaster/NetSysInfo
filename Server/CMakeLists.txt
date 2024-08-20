add_executable(start_server server.cpp
        include/server.h)

target_include_directories(start_server PUBLIC "/home/user/Projects/C++/Client-Server/Server/include")
