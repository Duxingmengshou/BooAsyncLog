# booAsyncLog/CMakeLists.txt
add_library(booAsyncLog STATIC
        asyncLog.cpp
        asyncLogBase.cpp
        logBuffer.h
        logFile.cpp
)

target_include_directories(booAsyncLog
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
