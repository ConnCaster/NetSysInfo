find_package(nlohmann_json PATHS "/home/user/Projects/C++/Client-Server/lib/include")

add_executable(start_server server.cpp
        include/server.h)

target_include_directories(start_server PUBLIC "/home/user/Projects/C++/Client-Server/lib/include"
                                                "/home/user/Projects/C++/Client-Server/Server/include")
