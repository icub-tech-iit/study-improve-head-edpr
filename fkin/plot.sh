#!/bin/bash

# Copyright (C) 2021 Fondazione Istituto Italiano di Tecnologia (IIT)  
# All Rights Reserved.

octave-cli octave-script.m $HOME/.local/share/yarp/contexts/fkin/frames.csv
gp open frames.png
