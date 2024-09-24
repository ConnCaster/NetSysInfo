add_executable(start_client client.cpp
        ../../include/client/client.h)

target_include_directories(start_client PUBLIC "${CMAKE_SOURCE_DIR}/lib/JSON/include"
                                                "${CMAKE_SOURCE_DIR}/include/client")