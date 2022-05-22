# Prizm Remote Control Box 

## EasyTransfer is required 
[Download here](https://github.com/madsci1016/Arduino-EasyTransfer) 

Copy the EasyTransferI2C folder into the arduino library folder

## Wiring
- Plug the wire from the box into the I2C slot on the prizm (top left slot if the green and red buttons are at the bottom).
- Servos must be wired to slot 1 or 2

## Prizm code 
- Download or copy the prizm.ino sketch from the prizm folder
- Open the downloaded sketch, or create a new sketch and copy the contents of prizm.ino
- Upload it to your prizm
- Press the green button on the prizm
- Drive!

## Troubleshooting

- If one of your motors are spinning in the wrong direction you may have to edit the following lines in prizm.ino
  ```cpp
    prizm.setMotorInvert(2,1);
    prizm.setMotorInvert(1,1);
  ```
  - Comment/uncomment based on your motor configuration

- If your motors are spinning without moving the controller, check the dials on your controller
  - They must be centered for the robot to function properly 


## Controls
- Left stick y-axis: forward/backward
- Left stick x-axis: spin left/right
- Right stick y-axis: servo 1
- Right stick x-axis: servo 2

### Arduino code
The arduino code is preloaded and shouldn't need to be touched.
