# Specify variables for generated code
set(TARGET ${BSP_TARGET_NAME})
set(GENERATED_CODE_ROOT_DIR ${CMAKE_BINARY_DIR}/generated/${HW_TARGET})
set(IOC_PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${HW_TARGET})
set(IOC_PROJECT_FILE_PATH ${IOC_PROJECT_ROOT_DIR}/${HW_TARGET}.ioc)

message("Configuring BSP for " ${HW_TARGET})

# Generate code with STM32CubeMX
find_program(STM32CUBEMX_GENERATOR STM32CubeMX
    HINTS
        $ENV{HOME}/STM32CubeMX
        ${STM32CUBEMX_GENERATOR_PATH}
    )

if(NOT STM32CUBEMX_GENERATOR)
    message(FATAL_ERROR "STM32CubeMX generator is not found.")
endif()

# Prepare generator script
configure_file(cubemx_generate.in ${GENERATED_CODE_ROOT_DIR}/cubemx_generate)

# Calculate hash of current project file
file(SHA256 ${IOC_PROJECT_FILE_PATH} CUBEMX_PROJECT_HASH_CURRENT)

# Add dependency on project file
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${IOC_PROJECT_FILE_PATH})

if(NOT "${CUBEMX_PROJECT_HASH_CURRENT}" STREQUAL "${CUBEMX_PROJECT_HASH}")

    message("Generating source code for BSP " ${HW_TARGET})
    execute_process(COMMAND
        java -jar ${STM32CUBEMX_GENERATOR} -q ${GENERATED_CODE_ROOT_DIR}/cubemx_generate)

    # Save hash of generated file
    file(SHA256 ${IOC_PROJECT_FILE_PATH} CUBEMX_PROJECT_HASH)
    set(CUBEMX_PROJECT_HASH "${CUBEMX_PROJECT_HASH}" CACHE INTERNAL CUBEMX_PROJECT_HASH FORCE)
endif()

file(GLOB_RECURSE SOURCES
    ${GENERATED_CODE_ROOT_DIR}/Drivers/*.c
    FreeRTOS/*.c
    ${GENERATED_CODE_ROOT_DIR}/Core/*.c
    ${GENERATED_CODE_ROOT_DIR}/Middlewares/ST/STM32_USB_Device_Library/Core/*.c
    ${GENERATED_CODE_ROOT_DIR}/Middlewares/Third_Party/*.c
    ${GENERATED_CODE_ROOT_DIR}/USB_DEVICE/Target/*.c
    ${GENERATED_CODE_ROOT_DIR}/*.s
)

file (GLOB_RECURSE LINKER_SCRIPT
        ${GENERATED_CODE_ROOT_DIR}/STM32*_FLASH.ld
)

# Exclude generated files which will be not used in a project
# Exclude main.c and freertos.c as they are not used
list(FILTER SOURCES EXCLUDE REGEX "main|freertos|cmsis_os.c")

add_library(${TARGET}
    ${SOURCES}
)

target_link_libraries(${TARGET} PUBLIC -T${LINKER_SCRIPT})

include(${CMAKE_CURRENT_SOURCE_DIR}/${HW_TARGET}/CMakeLists.txt)

target_include_directories(${TARGET}
    PUBLIC
        ${GENERATED_CODE_ROOT_DIR}/Core/Inc
        ${GENERATED_CODE_ROOT_DIR}/Drivers/${DEVICE_FAMILY}_HAL_Driver/Inc
        ${GENERATED_CODE_ROOT_DIR}/Drivers/CMSIS/Device/ST/${DEVICE_FAMILY}/Include
        ${GENERATED_CODE_ROOT_DIR}/Drivers/*/Inc/Legacy
        ${GENERATED_CODE_ROOT_DIR}/Drivers/CMSIS/Device/ST/${DEVICE_FAMILY}/Include
        ${GENERATED_CODE_ROOT_DIR}/Drivers/CMSIS/Include
        ${GENERATED_CODE_ROOT_DIR}/Middlewares/Third_Party/FreeRTOS/Source/include
        ${GENERATED_CODE_ROOT_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/
        ${GENERATED_CODE_ROOT_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/
        ${CMAKE_CURRENT_SOURCE_DIR}/${HW_TARGET}
        ${GENERATED_CODE_ROOT_DIR}/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
        ${GENERATED_CODE_ROOT_DIR}/USB_DEVICE/Target
)