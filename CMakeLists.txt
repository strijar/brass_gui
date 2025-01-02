cmake_minimum_required(VERSION 3.23)

set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_C_FLAGS_DEBUG "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O3")

project(brass_gui)

include_directories(.)
include_directories(third-party/rapidxml)
include_directories(third-party/utf8)

add_subdirectory(lvgl)
add_subdirectory(lv_drivers)
add_subdirectory(src)
add_subdirectory(sql)
