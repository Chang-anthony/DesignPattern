set(BIGTWO_LIB_NAME "BIGTWO_INCLUDE")
set(BIGTWO_LIB_INC_PATH ${CMAKE_CURRENT_LIST_DIR})

set(__BIGTWO_SRCS)

include(${BIGTWO_LIB_INC_PATH}/Player/player.cmake)
list(APPEND __BIGTWO_SRCS ${BIGTWO_LIB_SRCS})


include(${BIGTWO_LIB_INC_PATH}/Card/card.cmake)
list(APPEND __BIGTWO_SRCS ${BIGTWO_LIB_SRCS})

include(${BIGTWO_LIB_INC_PATH}/bigtwo/bigtwo.cmake)
list(APPEND __BIGTWO_SRCS ${BIGTWO_LIB_SRCS})


set(BIGTWO_LIB_SRCS ${__BIGTWO_SRCS})