add_executable(UM user_manager.cpp
        ${CMAKE_SOURCE_DIR}/include/userManager/user_manager.h)

target_include_directories(UM PUBLIC "${CMAKE_SOURCE_DIR}/lib/JSON/include"
                                             "${CMAKE_SOURCE_DIR}/include/database"
                                                    "${CMAKE_SOURCE_DIR}/include/userManager")