#README

##Protocol Instructions:

Commands are in format:
```
*command* *param1* *param2* ... *paramN*
```

All commands are sent in plaintext over bluetooth connection

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

###Repeat

Repeat a series of commands the specified number of *times*

```
repeat *times*
*command1*
*command2*
repeat end
```

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

