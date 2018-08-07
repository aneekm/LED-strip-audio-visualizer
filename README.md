# LED Audio Visualizer
## Arduino and Processing+Minim Project

This project was originally conceived in a Physical Computing class, when a group 
that was putting on a music and poetry session wanted responsive lighting. Having 
experience with Arduinos and LEDs, I figured getting an audo visualizer running 
on top of that would be a fun but simple challenge. It's been a few years since I
last tested this code but it should still work the same.

### Instructions for Use
The setup is simple: Install Processing on the main machine running the visualizer,
edit the Serial port assignment in the script to whatever serial port is connected
to your Arduino (USB), run the script, and **PLAY SOME MUSIC!**. Some instructions
for controlling the sensitivity and turning the visualizer temporarily on/off will 
be on the screen.

On the Arduino side, you need to have a NeoPixel LED strip hooked up (or a strip 
with the same control scheme. Otherwise, you will have to edit the Arduino code to
manually do the color loading or use your strip's library if it exists). The 'PIN'
variable near the top defines which pin on the Arduino is hooked up to the data pin
on the strip. Change if necessary. 
