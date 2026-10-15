set(LIB_NAME "SERVICE_SRC")
set(LIB_PATH ${CMAKE_CURRENT_LIST_DIR})

# src/ 底下所有 .cpp（含子資料夾）；新增 / 刪除檔案或資料夾不必改這裡
# CONFIGURE_DEPENDS：每次 build 都重新搜尋，檔案增減時會自動重跑 cmake
file(GLOB_RECURSE LIB_SRCS CONFIGURE_DEPENDS ${LIB_PATH}/*.cpp)
