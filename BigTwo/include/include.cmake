set(BIGTWO_LIB_NAME "BIGTWO_INCLUDE")
set(BIGTWO_LIB_INC_PATH ${CMAKE_CURRENT_LIST_DIR})

set(__BIGTWO_INCS
    "${BIGTWO_LIB_INC_PATH}/Card"
    "${BIGTWO_LIB_INC_PATH}/Player"
)

# GLOB 透過cmake 語法 搜尋 path 底下的 *hpp file
# file(GLOB __BIGTWO_INCS
#     "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/include/utils/*.hpp"
# )

set(BIGTWO_LIB_INCS ${__BIGTWO_INCS})