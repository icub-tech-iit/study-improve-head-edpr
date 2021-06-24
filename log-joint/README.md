# Log joint data
The snippet code allows moving a joint between two set points both in position and PWM control mode and logs the following joint data:

- PID reference
- PID output
- Joint encoder 
- Motor current
- Motor encoder 
- Pwm reading
- Torque

The matlab script plots the logged data

## Compile the code
In order to compile the [code](src/main.cpp) do :

```console
cd src
mkdir build
cd build
ccmake ..
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

### Pwm
This example moves the joint 3 of the head (eyes tilt) in pwm mode (setting the pwm to 70%) between -20 deg and +20 deg for 5 times (pausing on each set point 1 sec) and logs the data in a file called `mylog.log`.

```console
cd src/build

./log-joint --robot-part head --joint-id 3 --set-point1 -20 --set-point2 20 --cycles 5 --control-mode pwm --pwm-value 70 --pause 1 --log-file mylog.log
```

## Matlab script
Modify the script w/ the proper log file name and run it.
