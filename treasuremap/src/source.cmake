set(LIB_NAME "TREASUREMAP_INCLUDE")
set(LIB_PATH ${CMAKE_CURRENT_LIST_DIR})

set(__SRCS)

include(${LIB_PATH}/Mapobject/mapobject.cmake)
list(APPEND __SRCS ${LIB_SRCS})


# include(${LIB_INC_PATH}/Card/card.cmake)
# list(APPEND __SRCS ${BIGTWO_LIB_SRCS})

# include(${LIB_INC_PATH}/bigtwo/bigtwo.cmake)
# list(APPEND __SRCS ${BIGTWO_LIB_SRCS})


set(LIB_SRCS ${__SRCS})
