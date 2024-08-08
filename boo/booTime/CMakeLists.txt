# booTime/CMakeLists.txt
add_library(booTime STATIC
        booDate.cpp
)

target_include_directories(booTime
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
