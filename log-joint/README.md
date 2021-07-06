# Log joint data
The snippet code allows moving a joint between two set points both in position and PWM control mode and logs the following joint data:

- PID reference
- PID output
- Joint encoder 
- Motor current
- Motor encoder 
- PWM readouts
- Torque

The matlab script plots the logged data

## Compile the code
In order to compile the [code](src/main.cpp) do :

```console
cd src
cmake -S . -B build
cmake --build build
```

## Usage
It is possible to run the code to control the joint both in `position` and `PWM` control mode by passing to it proper parameters via CLI.
The parameters available are :

### Position
This example moves the joint 3 of the head (eyes tilt) in position mode between -20 deg and +20 deg for 5 times (pausing on each set point 1 sec) and logs the data in a file called `mylog.log`.

```console
cd src/build

./log-joint --robot-part head --joint-id 3 --set-point1 -20 --set-point2 20 --cycles 5 --control-mode position --pause 1 --log-file mylog.log
```

### PWM
This example moves the joint 3 of the head (eyes tilt) in PWM mode (setting the PWM to 70%) between -20 deg and +20 deg for 5 times (pausing on each set point 1 sec) and logs the data in a file called `mylog.log`.

```console
cd src/build

./log-joint --robot-part head --joint-id 3 --set-point1 -20 --set-point2 20 --cycles 5 --control-mode pwm --pwm-value 70 --pause 1 --log-file mylog.log
```

## Matlab script
Modify the script w/ the proper log file name and run it.

### Example of acquisitions plots and logs

## Position
### tilt
![image](https://user-images.githubusercontent.com/6638215/123105865-6f919100-d438-11eb-85a3-c2a5b39829d9.png)
### pan
![image](https://user-images.githubusercontent.com/6638215/123105946-80da9d80-d438-11eb-94f9-6a2dc1645dbf.png)

## Pwm 70%
### tilt
![image](https://user-images.githubusercontent.com/6638215/123106046-98198b00-d438-11eb-8136-a323f918aa44.png)
### pan
![image](https://user-images.githubusercontent.com/6638215/123106127-ab2c5b00-d438-11eb-8ca4-64e4fbc2edbc.png)

## Logs
[j3-pos.log](https://github.com/icub-tech-iit/fix/files/6702169/j3-pos.log)

[j3-pwm70.log](https://github.com/icub-tech-iit/fix/files/6702170/j3-pwm70.log)

[j4-pos.log](https://github.com/icub-tech-iit/fix/files/6702171/j4-pos.log)

[j4-pwm70.log](https://github.com/icub-tech-iit/fix/files/6702172/j4-pwm70.log)

