# pico_bootloader
Uses a rasperry pi picp as a USB to UART CDC
This project uses platformIO with VS code 

# useage
 ## pico setup
* make a mew project in platformIO
* replace main.cpp with the main provided here
* upload sketch
* make sure to check USB port permissions for platformIO if it does not work

 ## STM32 blue pill setup
|pico pin  ->   blue pill|
|------------|
| gpio 0   ->   pa 10|
| gpio 1   ->   pa 9 |

*remove BOOT0 header from 0 to 1

 ## platformIO setup
To upload code for the blue pill via USB to UART, put these in your configuartion file 

```
;...
monitor_speed = 115200    ; set the baud rate to 115200
upload_protocol = serial  ; upload the code via USB rather than platformIO's default
;...
```

 
 ## uploading code 

after flashing the pi pico and wireing to the stm32  
* open a serial monitor where the pico is at 115200
  - the led on pin 25 shoudl light
  - if the light does not turn on, unplug and trying again may work
  - double check your've selected the right port for the USB
* complile and upload your code for the blue pill

<br><br>
<br><br>
