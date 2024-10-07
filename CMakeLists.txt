cmake_minimum_required(VERSION 3.23)

project(brass_gui)

include_directories(.)
include_directories(third-party/rapidxml)
include_directories(third-party/utf8)

add_subdirectory(lvgl)
add_subdirectory(src)
add_subdirectory(sql)

set(LV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h CACHE STRING "" FORCE)
