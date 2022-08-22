set (TARGET "nice-bsp")

add_library(${TARGET}
    src/error/SystemErrorHandler.cpp
    src/gpio/GPIO.cpp
    src/bsp_extension/BspExtension.cpp
)

target_include_directories(${TARGET}
    PUBLIC
        include/
    PRIVATE
        include/nice-bsp/error
        include/nice-bsp/gpio
        include/nice-bsp/led
)

target_link_libraries(${TARGET}
    PUBLIC
        ${BSP_TARGET_NAME}
)