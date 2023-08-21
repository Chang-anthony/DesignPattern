cmake_minimum_required(VERSION 3.12)

project(MyApp)

# 將所有源檔案放入變數中
set(SOURCES
    main.cpp
    # CheckMissionState.cpp
)

# 指定項目的執行檔名稱和源檔
add_executable(${PROJECT_NAME} ${SOURCES})

# 將項目的 include 路徑設定為當前目錄（或是你的標頭檔所在的目錄）
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 設定項目的目標特性，比如 C++ 版本
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)