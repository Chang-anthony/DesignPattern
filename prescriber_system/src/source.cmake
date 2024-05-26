set(LIB_NAME "PRESCRIBER_SRC")
set(LIB_PATH ${CMAKE_CURRENT_LIST_DIR})

set(__SRCS
    ${LIB_PATH}/Database.cpp
    ${LIB_PATH}/Patient.cpp
    ${LIB_PATH}/Case.cpp
    ${LIB_PATH}/Prescription.cpp
    ${LIB_PATH}/DiagnosticRules.cpp
    ${LIB_PATH}/Prescriber.cpp
    ${LIB_PATH}/SaveDiagnositic.cpp
    ${LIB_PATH}/SaveJson.cpp
    ${LIB_PATH}/SaveCsv.cpp
)


# include(${LIB_PATH}/Mapobject/mapobject.cmake)
# list(APPEND __SRCS ${LIB_SRCS})

# message("${LIB_PATH}")


set(LIB_SRCS ${__SRCS})
