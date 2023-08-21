cmake_minimum_required(VERSION 3.12)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project(Designpattern_Cs_1_2)
set(CMAKE_CXX_STANDARD 20)

#加入include directories 位置
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include/utils)


# 將所有源檔案放入變數中
set(SOURCES
    main.cpp
)

#靜態函式庫
add_library(SimpleDesignPattern STATIC
    #source files
    src/CheckMissionState.cpp
    src/Student.cpp
    src/Mission.cpp
    src/LevelSheet.cpp
    src/Journey.cpp
    src/Challenge.cpp
    src/Chapter.cpp
    src/Scene.cpp
    src/VideoScene.cpp
    src/ContentScene.cpp

    #Header files
    # include/Chapter.h
    # include/CheckMissionState.h
    # include/ContentScene.h
    # include/Journey.h
    # include/LevelSheet.h
    # include/Mission.h
    # include/Scene.h
    # include/Student.h
    # include/VideoScene.h
    # include/Challenge.h
)

# 設置MSVC編譯編碼
# add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 指定項目的執行檔名稱和源檔
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} SimpleDesignPattern)

# 將項目的 include 路徑設定為當前目錄（或是你的標頭檔所在的目錄）
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/utils)

# 設定項目的目標特性，比如 C++ 版本
# target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
