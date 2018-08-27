# iButler

iButler is a robotics project that controls an iRobot/Roomba device through hand gestures. 
The main development language is `C`, and the hardware that was used includes Digilent's 
FPGA, Spartan-6, and Digilent's camera module VmodCAM.

The project detects changes in pixel density and RGB values to keep track of your hand's 
location relative to the camera's field of view. There is a complex FSM that orchestrates
the iRobot's movements based on completion of any one of the programmed hand gestures.
