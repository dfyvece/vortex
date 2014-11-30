#README

##Animations:
Animations are in format:
```
*animation_name* *duration* *param1* ... *paramN*
```
All durations are in milliseconds.

###Pulse

Strobe all lights at once

```
pulse *duration* *color*
```

###Spiral

Perform a circular sweep around the lights

```
spiral *duration* *color1* *color2* *color3* *color4*
```
 
*color2*, *color3*, and *color4* are optional.

##Commands
Commands are in format:
```
*command* *param1* *param2* ... *paramN*
```
Commands allow you to easily perform more complex interactions.

###Repeat

Repeat a series of commands the specified number of *times*

```
repeat *times*
*command1*
*command2*
repeat end
```

###Reverse

Reverse the order that an animation is performed.

```
reverse *command*
```
Note: *reverse repeat x* will not work, you must reverse the order that the commands are sent


##Colors

You can specify any of the following colors by name:
* Red
* Orange
* Yellow
* Green
* Blue
* Purple

You can also do custom colors in the format:
```
custom(*r*,*g*,*b*)
```

Where *r*,*g*, and *b* are integers [0-255]

