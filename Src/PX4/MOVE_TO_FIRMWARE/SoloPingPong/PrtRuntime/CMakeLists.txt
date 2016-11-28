cmake_minimum_required(VERSION 3.5)

include_directories(${YOUR_DIRECTORY})

set(C_INCLUDES ${YOUR_DIRECTORY})

add_definitions(-DPRT_PLAT_LINUXUSER)

add_library(PrtRuntime 
Prt.c
PrtTypes.c
PrtValues.c
PrtExecution.c
PrtUser.c
PrtLinuxUserConfig.c
SafeString.c
${YOUR_DIRECTORY}PrtConfig.h
${YOUR_DIRECTORY}PrtDistConfigParser.h
${YOUR_DIRECTORY}PrtLinuxUserConfig.h
${YOUR_DIRECTORY}PrtValues.h
${YOUR_DIRECTORY}PrtDist.h
${YOUR_DIRECTORY}PrtProgram.h
${YOUR_DIRECTORY}PrtValues_IDL.h
${YOUR_DIRECTORY}PrtDistIDL_h.h
${YOUR_DIRECTORY}PrtDistInternals.h
${YOUR_DIRECTORY}PrtTypes.h
${YOUR_DIRECTORY}SafeString.h
${YOUR_DIRECTORY}NodeManager_h.h
${YOUR_DIRECTORY}PrtTypes_IDL.h
${YOUR_DIRECTORY}PrtBaseTypes_IDL.h
${YOUR_DIRECTORY}PrtExecution.h
${YOUR_DIRECTORY}Prt.h
${YOUR_DIRECTORY}PrtUser.h
)


