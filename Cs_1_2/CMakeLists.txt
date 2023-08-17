cmake_minimum_required(VERSION 3.12)
project(Cs_1_2)

set(CMAKE_CXX_STANDARD 20)

# 如果代码需要支持C++11，就直接加上这句
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
# 如果想要生成的可执行文件拥有符号表，可以gdb调试，就直接加上这句
# add_definitions("-Wall -g")

# 设置变量，下面的代码都可以用到
# set(GOOGLE_PROTOBUF_DIR ${PROJECT_SOURCE_DIR}/protobuf)
# set(PROTO_PB_DIR ${PROJECT_SOURCE_DIR}/proto_pb2)
# set(PROTO_BUF_DIR ${PROJECT_SOURCE_DIR}/proto_buf)

set(UTILS ${PROJECT_SOURCE_DIR}/include)

# 编译子文件夹的CMakeLists.txt
# add_subdirectory(proto_pb2)

# 规定.h头文件路径
include_directories(${PROJECT_SOURCE_DIR}
    ${UTILS} 
)
set(SOURCES
    main.cpp
    CheckMissionState.cpp
)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 链接操作
# target_link_libraries(${PROJECT_NAME})
