set(LIB_NAME "YTChannel_LIB")
set(LIB_PATH ${CMAKE_CURRENT_LIST_DIR})

# Cmake 變數在整個專案都可以訪問到，即全域變數，要注意越底部的資料要定義的變數名稱要加上底線

set(__LIB_SRCS)
set(__LIB_INCS)

include(${LIB_PATH}/Channel/channel.cmake)
list(APPEND __LIB_INCS ${__INCS})
list(APPEND __LIB_SRCS ${__SRCS})

include(${LIB_PATH}/Subscriber/subscriber.cmake)
list(APPEND __LIB_INCS ${__INCS})
list(APPEND __LIB_SRCS ${__SRCS})

set(LIB_SRCS ${__LIB_SRCS})
set(LIB_INCS ${__LIB_INCS})