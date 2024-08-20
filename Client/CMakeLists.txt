add_executable(start_client client.cpp
        include/client.h)

target_include_directories(start_client PUBLIC "/home/user/Projects/C++/Client-Server/Client/include")
