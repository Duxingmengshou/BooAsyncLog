# booThread/CMakeLists.txt
add_library(booThread STATIC
        countDownLatch.cpp
)

target_include_directories(booThread
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
