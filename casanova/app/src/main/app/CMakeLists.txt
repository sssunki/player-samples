cmake_minimum_required(VERSION 3.10.2)
add_library(
        avcodec
        SHARED
        IMPORTED
)
set_target_properties(
        avcodec
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/ffmpeg/armeabi-v7a/libavcodec.so
)

add_library(
        avfilter
        SHARED
        IMPORTED
)
set_target_properties(
        avfilter
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/ffmpeg/armeabi-v7a/libavfilter.so
)

add_library(
        avformat
        SHARED
        IMPORTED
)
set_target_properties(
        avformat
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/ffmpeg/armeabi-v7a/libavformat.so
)

add_library(
        avutil
        SHARED
        IMPORTED
)
set_target_properties(
        avutil
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/ffmpeg/armeabi-v7a/libavutil.so
)

add_library(
        swresample
        SHARED
        IMPORTED
)
set_target_properties(
        swresample
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/ffmpeg/armeabi-v7a/libswresample.so
)

add_library(
        swscale
        SHARED
        IMPORTED
)
set_target_properties(
        swscale
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/ffmpeg/armeabi-v7a/libswscale.so
)

add_library(
    my-sdk
    SHARED
    ${CMAKE_SOURCE_DIR}/jnicall.cpp)
set_target_properties(my-sdk PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(
        my-sdk
        avcodec
        avfilter
        avformat
        avutil
        swresample
        swscale
        android
        log)