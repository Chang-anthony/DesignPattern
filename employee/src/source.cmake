set(LIB_NAME "EMPLOYEE_SRC")
set(LIB_PATH ${CMAKE_CURRENT_LIST_DIR})

set(__SRCS
    ${LIB_PATH}/Employee.cpp
    ${LIB_PATH}/RealEmployee.cpp
    ${LIB_PATH}/Database.cpp
    ${LIB_PATH}/RealDatabase.cpp
)


# include(${LIB_PATH}/Mapobject/mapobject.cmake)
# list(APPEND __SRCS ${LIB_SRCS})

# message("${LIB_PATH}")


set(LIB_SRCS ${__SRCS})
