add_executable(DB file_handler.cpp
        ../../include/database/file_handler.h)

target_include_directories(DB PUBLIC "${CMAKE_SOURCE_DIR}/lib/JSON/include"
                                        "${CMAKE_SOURCE_DIR}/include/database")