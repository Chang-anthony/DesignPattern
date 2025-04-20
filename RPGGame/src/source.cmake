set(LIB_NAME "RPGGAAME_SRC")
set(LIB_PATH ${CMAKE_CURRENT_LIST_DIR})

set(__SRCS
)

include(${LIB_PATH}/Skill/skill.cmake)
list(APPEND __SRCS ${LIB_SRCS})

include(${LIB_PATH}/Role/role.cmake)
list(APPEND __SRCS ${LIB_SRCS})

include(${LIB_PATH}/Observer/observer.cmake)
list(APPEND __SRCS ${LIB_SRCS})
# include(${LIB_PATH}/Mapobject/mapobject.cmake)
# list(APPEND __SRCS ${LIB_SRCS})
# message("${LIB_PATH}")


set(LIB_SRCS ${__SRCS})
