set(__NAME "test_interface")
set(__LIB_PATH ${CMAKE_CURRENT_LIST_DIR})

set(__TEST_UTILS__SRCS 
    ${__LIB_PATH}/FileIterator/FileLine.cpp
    ${__LIB_PATH}/FileIterator/FileIterator.cpp
)

# Client 端的原始碼（例如解析輸入的 parser）放這裡：編進主程式的 library，main.cpp 與測試共用；
# 不放進 __TEST_UTILS__SRCS，因為 SimpleTest_LIB 看不到模組的標頭檔。目前沒有
set(__CLIENT_SRCS
)

set(__TEST_UTILS_INCS
    ${__LIB_PATH}
    ${__LIB_PATH}/FileIterator

)

