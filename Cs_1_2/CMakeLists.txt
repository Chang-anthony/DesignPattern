cmake_minimum_required(VERSION 3.12)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project(MyApp)
set(CMAKE_CXX_STANDARD 20)

# 將所有源檔案放入變數中
set(SOURCES
    main.cpp
    # CheckMissionState.cpp
)

add_library(SimpleDesignPattern STATIC
    #source files
    CheckMissionState.cpp

    #Header files
    Challenge.h
    Chapter.h
    CheckMissionState.h
    ContentScene.h
    Journey.h
    LevelSheet.h
    Mission.h
    Scene.h
    Student.h
    VideoScene.h
)

# 指定項目的執行檔名稱和源檔
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} SimpleDesignPattern)

# 將項目的 include 路徑設定為當前目錄（或是你的標頭檔所在的目錄）
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 設定項目的目標特性，比如 C++ 版本
# target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
