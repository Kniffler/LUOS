# LUOS
Not really an OS but meh, nobody can stop me.

## Desc.
This bad boy uses FreeRTOS alongside a basic set of commands I have defined. There are currently two types of commands: system directives and user-space commands.

System directives, as the name implies, are commands that concern themselves with the inner workings of the system, these are mainly used for debugging as of now.
User-space commands are exactly what they sound like, they are used to open various applications, configure them, and more.

## UI
As of now there is no coherent UI design implemented, I have some ideas in mind but they require a good bit of reworking in the lcdspi library. While LVGL is compatible, I would prefer an all-ASCII design, not only to lessen the load on the device (a pico 2w in my case) but also for a pleasing and consistent aesthetic. 
