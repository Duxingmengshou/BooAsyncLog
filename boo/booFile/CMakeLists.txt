# booFile/CMakeLists.txt
add_library(booFile STATIC
        fileName.cpp
        fileWrite.cpp
)

target_include_directories(booFile
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
