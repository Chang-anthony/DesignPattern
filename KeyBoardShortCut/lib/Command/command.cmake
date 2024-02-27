set(__LIB_NAME "command")
set(__LIB_PATH ${CMAKE_CURRENT_LIST_DIR})

set(__SRCS
    ${__LIB_PATH}/Command.cpp
    ${__LIB_PATH}/TankMoveForwardCommand.cpp
    ${__LIB_PATH}/TankMoveBackwardCommand.cpp
    ${__LIB_PATH}/TelecomConnectCommand.cpp
    ${__LIB_PATH}/TelecomdisConnectCommand.cpp

)