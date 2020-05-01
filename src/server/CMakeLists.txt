
include(${CMAKE_CURRENT_LIST_DIR}/routes/CMakeLists.txt)

target_sources(restx_common PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Server.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Server.h
)