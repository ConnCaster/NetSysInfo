#find_package(nlohmann_json PATHS "/home/user/Projects/C++/Client-Server/lib/include")

add_executable(start_client client.cpp
        include/client.h)

target_include_directories(start_client PUBLIC "/home/user/Projects/C++/Client-Server/lib/include"
                                                "/home/user/Projects/C++/Client-Server/Client/include")
