set(__NAME "test_interface")
set(__LIB_PATH ${CMAKE_CURRENT_LIST_DIR})

set(__TEST_UTILS__SRCS 
    ${__LIB_PATH}/FileIterator/FileLine.cpp
    ${__LIB_PATH}/FileIterator/FileIterator.cpp
)

# Client 端：解析測資 / 輸入、技能名稱 → 技能（D26、D36）。編進主程式的 library，main.cpp 與測試共用；
# 不放進 __TEST_UTILS__SRCS，因為 SimpleTest_LIB 看不到模組的標頭檔
set(__RPG_CLIENT_SRCS
    ${__LIB_PATH}/RPG_parser.cpp
)

set(__TEST_UTILS_INCS
    ${__LIB_PATH}
    ${__LIB_PATH}/FileIterator

)

