#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.7)

# specify cross compilers and tools
SET(CMAKE_C_COMPILER_WORKS 1)
SET(CMAKE_C_COMPILER arm-none-eabi-gcc)
SET(CMAKE_CXX_COMPILER_WORKS 1)
SET(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)

if (DEFINED DEVICE_FAMILY)
    add_compile_definitions(${DEVICE_FAMILY})
else()
    message(FATAL_ERROR " DEVICE_FAMILY is not specified")
endif()

if(${DEVICE_FAMILY} MATCHES "STM32F4[A-Z]*")
    message("Enabling HW floating point")
    SET(FPU_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16")
    add_definitions(-DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING)
    set(ARM_CORE "-mcpu=cortex-m4")
else()
    message("Enabling SW floating point")
    SET(FPU_FLAGS "-mfloat-abi=soft")
    set(ARM_CORE "-mcpu=cortex-m3")
endif()

SET(COMMON_FLAGS
    "${ARM_CORE} ${FPU_FLAGS} -mthumb -mthumb-interwork -ffunction-sections -fdata-sections \
    -g -fno-common -fmessage-length=0 -specs=nosys.specs -specs=nano.specs")

SET(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -std=c++14")
SET(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS} -std=gnu11")
#SET(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,-gc-sections,--print-memory-usage -T ${LINKER_SCRIPT}")

PROJECT(modern-cmake-stm32 C CXX ASM)

set(CMAKE_CXX_STANDARD 14)

# TODO: HW specific part
#add_definitions(-DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -D__FPU_PRESENT=1)
add_definitions(-DUSE_HAL_DRIVER)


# Define BSP library name
if (DEFINED HW_TARGET)
    set(BSP_TARGET_NAME ${HW_TARGET}_bsp_lib)
else()
    message(FATAL_ERROR " Target hardware is not specified")
endif()

add_subdirectory(bsp)
add_subdirectory(lib/nice-bsp)
add_subdirectory(src)
