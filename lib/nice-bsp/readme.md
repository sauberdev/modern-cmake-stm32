#### User friendly BSP

The aim of this library is provide library with an access to hardware,
but in the same time with convenient C++ API.

#### Dependencies

- BSP for selected hardware

##### Limitations

`nice-bsp` overrides the BSP method `HAL_Delay` and uses FreeRTOS functionality. So please be aware of that and make sure that all methods
using this functionality called from FreeRTOS tasks.
