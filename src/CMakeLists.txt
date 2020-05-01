set(CMAKE_CXX_STANDARD 14)

add_library(restx_common)

add_definitions(-DXPLM301=1 -DXPLM300=1 -DXPLM210=1 -DXPLM200=1)

include(${CMAKE_CURRENT_LIST_DIR}/server/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/lib/CMakeLists.txt)

include_directories(
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/build-third/include"
    "${PROJECT_SOURCE_DIR}/lib/"
    )

add_definitions(-DCURL_STATICLIB)

target_link_libraries(restx_common
    "-F${PROJECT_SOURCE_DIR}/build-third/lib/ -framework XPLM"
    "${PROJECT_SOURCE_DIR}/build-third/lib/librestbed.a"
)


# X-Plane plugin
add_library(restx_plugin SHARED
    ${CMAKE_CURRENT_LIST_DIR}/Plugin.cpp
)

if(WIN32)
    add_definitions(-DIBM=1)
    target_link_libraries(restx_plugin
        -static
        -static-libgcc
        -static-libstdc++
        restx_common
        ${PROJECT_SOURCE_DIR}/build-third/lib/librestbed.a
        ${PROJECT_SOURCE_DIR}/build-third/lib/XPLM_64.lib
    )
elseif(APPLE)
    add_definitions(-DAPL=1)
    target_link_libraries(restx_plugin
        restx_common
        ${PROJECT_SOURCE_DIR}/build-third/lib/librestbed.a
        "-F${PROJECT_SOURCE_DIR}/build-third/lib/ -framework XPLM"
    )
elseif(UNIX)
    add_definitions(-DLIN=1)
    target_link_libraries(restx_plugin
        -static-libgcc
        -static-libstdc++
        restx_common
        ${PROJECT_SOURCE_DIR}/build-third/lib/librestbed.a
        "-F${PROJECT_SOURCE_DIR}/build-third/lib/ -framework XPLM"
    )
endif()


set_target_properties(restx_plugin PROPERTIES PREFIX "")

if(APPLE)
	set_target_properties(restx_plugin PROPERTIES OUTPUT_NAME "mac")
elseif(UNIX)
	set_target_properties(restx_plugin PROPERTIES OUTPUT_NAME "lin")
elseif(WIN32)
	set_target_properties(restx_plugin PROPERTIES OUTPUT_NAME "win")
endif()

set_target_properties(restx_plugin PROPERTIES SUFFIX ".xpl")