set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

set(CMAKE_CXX_FLAGS -mthumb-interwork -mfloat-abi=hard -mfpu=neon -mtune=cortex-a9 -march=armv7-a)





