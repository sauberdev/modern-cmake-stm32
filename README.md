# modern-cmake-stm32
Small project to demonstrate how to develop SW for STM32 MCU's using modern CMake and CubeMX.

## Description
This project aims to demonstrate how the modern CMake and STM32CubeMX
might be used for efficient SW development for the STM32 family of MCU's. 
The main goal is to abstract the user firmware from the STM32 HW specific details
and allow easily switch between different boards.

The whole project is separated in three levels:

- User firmware
- nice-bsp
- bsp

### bsp
To allow easily configure and re-configure the HW, it was decided
to use the GUI tool CubeMX. It allows to configure clocks, peripherals
and middleware used by the project. At the end it would just generate
project file in `ioc` format which will be used during build for code 
generation. At the end a static lib will be provided which will be used
later by `nice-bsp` library.

### nice-bsp
The `nice-bsp` library is going to provide an easy to use API to configure, initialize
and control the HW. It abstracts the user firmware from BSP layer by
providing a convenient C++ API.

### User firmware
User firmware is the last layer of the project. It doesn't use directly
`bsp` layer, but already consuming C++ API's coming from `nice-bsp` layer and in that way
abstracted from HW interface.

## Dependencies
- STM32CubeMX

## Build instructions

### How to add a new device

- Create a new folder under `bsp` with a board name
- Add `FreeRTOSConfig.h` as the configuration may vary depending on the board
- Create a new project with `STM32CubeMX` for this board, configure
  and save target `*.ioc` under `bsp/board_name`
- Provide a linker file for a new device under `linker_scripts`  
- Create a `CMakeLists.txt` which would specify device family in a format `STM32FYXX`
  where Y is the number of device family and add compile definition with
  the MCU name, e.g:
```cmake
add_compile_definitions(STM32F407xx)
set(DEVICE_FAMILY "STM32F4xx")
```

## How to build

### Configuration
- Specify desired device via CMake variable `HW_TARGET`, e.g.:
`-DHW_TARGET=stm32f4_discovery`
- Set path to STM32CubeMX generator via CMake variable `STM32CUBEMX_GENERATOR_PATH`
- Specify device family using `DEVICE_FAMILY`, e.g.: `-DDEVICE_FAMILY=STM32F401xC`

### Build
Just run CMake with configured variables specified above and afterward run make.
It would generate `bsp` and `nice-bsp` libraries for the desired HW and
the user firmware code may stay unchanged.

## Flash&Debug with OpenOCD

### STM32F2xx
- Select as a board config file `board/stm3220g_eval_stlink.cfg`
- Replace there `reset_config srst_only` with `reset_config none separate`
- Now you should be able to flash and debug source code

To debug peripherals you may need SVD file for used processor:

- For STM32F20xx it's located under `svd\STM32F20x.svd`