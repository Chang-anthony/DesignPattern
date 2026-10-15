set(LIB_NAME "SERVICE_INCLUDE")
set(LIB_INC_PATH ${CMAKE_CURRENT_LIST_DIR})

# include/ 底下的每個子資料夾都加進 include 路徑；新增資料夾不必改這裡
set(__INCS ${LIB_INC_PATH})
file(GLOB __CHILDREN LIST_DIRECTORIES true ${LIB_INC_PATH}/*)
foreach(__CHILD ${__CHILDREN})
    if(IS_DIRECTORY ${__CHILD})
        list(APPEND __INCS ${__CHILD})
    endif()
endforeach()

set(LIB_INCS ${__INCS})
