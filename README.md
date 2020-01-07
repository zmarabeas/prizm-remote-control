# Prizm Remote Control Box 

## EasyTransfer is required 

	[Download here](https://github.com/madsci1016/Arduino-EasyTransfer) 
	Copy the EasyTransferI2C folder into the arduino library folder

## Instructions

	Download or copy the prizm.ino sketch from the prizm folder.
	Open the downloaded sketch, or create a new sketch and copy the contents of prizm.ino into your new sketch.
	Upload it to your prizm.

	If one of your motors are spinning in the wrong direction you may have to edit the following lines in prizm.ino.
		```cpp
		prizm.setMotorInvert(2,1);
  	prizm.setMotorInvert(1,1);
  	```
  Comment/uncomment based on your motor configuration.

  If your motors are spinning without moving the controller, check if the dials on your controller are centered.