set(LIB_NAME "PRESCRIBER_SRC")
set(LIB_PATH ${CMAKE_CURRENT_LIST_DIR})

set(__SRCS
    ${LIB_PATH}/Relation.cpp
    ${LIB_PATH}/Friends.cpp
    ${LIB_PATH}/Graph.cpp
)


# include(${LIB_PATH}/Mapobject/mapobject.cmake)
# list(APPEND __SRCS ${LIB_SRCS})

# message("${LIB_PATH}")


set(LIB_SRCS ${__SRCS})
