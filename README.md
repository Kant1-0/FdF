![42-Project](https://dl.dropboxusercontent.com/u/59532932/48-cole204220logo.png)
#FdF 
Ray-tracer to parse a map given in paramater. Usage: ./fdf maps/42.fdf<br>
It will output thanks to the use of the graphic library: minilibx a 3D wireframe representation of the map.

#### Usual Map format
0 0  0  0 0<br>
0 10 10 0 0<br>
0 0  0  0 0<br>
#### Map format with Hex colors
0 0  0  0 0<br>
0 10,0xFF 10,0xFF 0 0<br>
0 0  0  0 0<br>



## Bonus
* Linear interpolation between two given colors to raytrace a gradient line
* Handle Hex color formating (with short format 0,0xff00 = 0,0x00ff00)
* Move, zoom and height can be change throw arrows, +, -, pgUp and phDwn (Mac keyboard Input)
* 5 key will reset the view
* Dynamic window of creating according to the size of the map
* Code basically made to handle different image / expose at the same time
