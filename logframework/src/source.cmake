set(LIB_NAME "LOGFRAMEWORK_SRC")
set(LIB_PATH ${CMAKE_CURRENT_LIST_DIR})

set(__SRCS
    ${LIB_PATH}/Layout.cpp
    ${LIB_PATH}/StandardLayout.cpp
    ${LIB_PATH}/Logger.cpp
    ${LIB_PATH}/Exporter.cpp
    ${LIB_PATH}/ConsoleExporter.cpp
    ${LIB_PATH}/FileExporter.cpp
    ${LIB_PATH}/CompositeExporter.cpp
    ${LIB_PATH}/Log.cpp
    ${LIB_PATH}/Level.cpp
)


# include(${LIB_PATH}/Mapobject/mapobject.cmake)
# list(APPEND __SRCS ${LIB_SRCS})

# message("${LIB_PATH}")


set(LIB_SRCS ${__SRCS})
