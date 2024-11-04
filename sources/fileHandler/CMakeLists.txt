add_executable(DB file_handler.cpp)

target_include_directories(DB PUBLIC "${CMAKE_SOURCE_DIR}/lib/JSON/include"
                                                "${CMAKE_SOURCE_DIR}/include/server"
                                                "${CMAKE_SOURCE_DIR}/include/fileHandler"
                                                "${CMAKE_SOURCE_DIR}/include/userManager")