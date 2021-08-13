/******************************************************************************
 *                                                                            *
 * Copyright (C) 2020 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 * Authors: davide.tome@iit.it                                                *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <cmath>
#include <limits>
#include <vector>
#include <fstream>

#include <yarp/os/Network.h>
#include <yarp/os/Time.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/ResourceFinder.h>
#include <yarp/os/Value.h>
#include <yarp/os/Bottle.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/IControlLimits.h>
#include <yarp/dev/IPositionControl.h>
#include <yarp/dev/IPidControl.h>
#include <yarp/dev/IControlMode.h>
#include <yarp/dev/IEncoders.h>
#include <yarp/dev/ICurrentControl.h> 
#include <yarp/dev/IMotorEncoders.h> 
#include <yarp/dev/IPWMControl.h>
#include <yarp/dev/ITorqueControl.h>




using namespace yarp::os;
using namespace yarp::dev;

struct DataExperiment {
    double t;
    double pid_ref;
    double pid_out;
    double enc;
    double curr;
    double motor_enc;
    double pwm_read;
    double pwm_set;
    double torque;
};

int main(int argc, char * argv[])
{
    Network yarp;
    if (!yarp.checkNetwork()) {
        yError() << "Unable to find YARP server!";
        return EXIT_FAILURE;
    }

    ResourceFinder rf;
    rf.configure(argc, argv);

    auto joint_id = rf.check("joint-id", Value(-1)).asInt();
    auto set_point1 = rf.check("set-point1", Value(0.)).asDouble();
    auto set_point2 = rf.check("set-point2", Value(0.)).asDouble();
    auto cycles = rf.check("cycles", Value(1)).asInt();
    auto T = rf.check("T", Value(2.)).asDouble();
    auto robot_part = rf.check("robot-part", Value("")).asString();
    auto log_file = rf.check("log-file", Value("output.log")).asString();
    auto time_delay = rf.check("time-delay", Value(.01)).asDouble();
    auto control_mode = rf.check("control-mode", Value("position")).asString();
    auto pwm_value = rf.check("pwm-value", Value(80.)).asDouble();
    auto pause = rf.check("pause", Value(1.)).asDouble();
    auto velocity = rf.check("velocity", Value(1)).asDouble();



    PolyDriver m_driver;
    IControlLimits* iLim{ nullptr };
    IPositionControl* iPos{ nullptr };
    IPidControl* iPid{ nullptr };
    IControlMode* iCm{ nullptr };
    IEncoders* iEnc{ nullptr };
    ICurrentControl * iCurr{ nullptr };
    IMotorEncoders * iMotorEnc{ nullptr };
    IPWMControl* iPwm{ nullptr };
    ITorqueControl* iTrq{nullptr};

    //for yarpscope
//    yarp::os::Bottle b;
    // yarp::os::BufferedPort<yarp::os::Bottle> port;

    // port.open("/log-joint");
    

    std::ofstream file;
    auto set_point = set_point1;

    file.open(log_file);

    std::vector<DataExperiment> data_vec;
    data_vec.reserve(1000);

    if (robot_part == ""){
       
        yError() << "No robot part selected..(use --robot-part option)";
        return EXIT_FAILURE;
    }

    Property conf;
    conf.put("device", "remote_controlboard");
    conf.put("remote", "/icub/" + robot_part);
    conf.put("local", "/logger");
    if (!m_driver.open(conf)) {
        yError() << "Failed to open";
        return EXIT_FAILURE;
    }
    if (!(m_driver.view(iPos) && m_driver.view(iPid) &&
          m_driver.view(iCm) && m_driver.view(iEnc) && 
          m_driver.view(iCurr) && m_driver.view(iMotorEnc) &&
          m_driver.view(iPwm) && m_driver.view(iTrq)) &&
          m_driver.view(iLim)) {
        m_driver.close();
        yError() << "Failed to view interfaces";
        return EXIT_FAILURE;
    }

    // int nAxes;
    // iEnc->getAxes(&nAxes);
    // if ((joint_id < 0) || (joint_id >= nAxes)) {
    //     m_driver.close();
    //     yError() << "joint_id is not within the correct range";
    //     return EXIT_FAILURE;
    // }

    // double joint_min, joint_max;
    // iLim->getLimits(joint_id, &joint_min, &joint_max);
    // if ((set_point1 < joint_min) || (set_point1 > joint_max) ||
    //     (set_point2 < joint_min) || (set_point2 > joint_max) ||
    //     (set_point1 > set_point2)) {
    //     m_driver.close();
    //     yError() << "set_point1 and/or set_point2 are not correct";
    //     return EXIT_FAILURE;
    // }
    

    auto t0 = Time::now();
    iCm->setControlMode(joint_id, VOCAB_CM_POSITION);

    // Homing
     iPos->setRefSpeed(joint_id, 25.);
     iPos->setRefAcceleration(joint_id, std::numeric_limits<double>::max());
     iPos->positionMove(joint_id, 0.);
     auto done{ false };
     while (!done) {
        iPos->checkMotionDone(joint_id, &done);
        Time::yield();
     }
    bool toggle = false;

    
    for(int i=0; i<(cycles*2); i++) {
        

        if(!toggle) set_point = set_point1;
        else set_point = set_point2;
        toggle = !toggle;
        DataExperiment data;
        
        iEnc->getEncoder(joint_id, &data.enc);
        iCurr->getCurrent(joint_id, &data.curr);
        iMotorEnc->getMotorEncoder(joint_id, &data.motor_enc);
        auto vel = std::fabs(set_point - data.enc) / T;
        if(velocity == 1) velocity = vel;

        iPwm->getDutyCycle(joint_id, &data.pwm_read);
        iTrq->getTorque(joint_id, &data.torque);

        if(control_mode == "position" ){
            iCm->setControlMode(joint_id, VOCAB_CM_POSITION);
            iPos->setRefSpeed(joint_id, velocity);
            iPos->positionMove(joint_id, set_point);
        }
        else if (control_mode == "pwm" ){
            //if (set_point > 0) pwm_value = pwm_value * -1;
            
            // iCm->setControlMode(joint_id, VOCAB_CM_PWM);
            // iPwm->setRefDutyCycle(joint_id, pwm_value);
            // //check movement direction
            // double enc1;
            // iEnc->getEncoder(joint_id, &enc1);
            // Time::delay(.02);
            // double enc2;
            // iEnc->getEncoder(joint_id, &enc2);
            // if(set_point > 0 && enc1 > enc2 && i == 0){
            //     pwm_value = pwm_value * -1;
            //     iPwm->setRefDutyCycle(joint_id, pwm_value);
            // }
            // if(set_point < 0 && enc2 < enc1 && i == 0){
            //     pwm_value = pwm_value * -1;
            //     iPwm->setRefDutyCycle(joint_id, pwm_value);
            // }                          

            Pid pidInfo;
            iPid->getPid(VOCAB_PIDTYPE_POSITION,joint_id,&pidInfo);
            auto pid_sign=(pidInfo.kp>=0.0?1.0:-1.0);

            if((pid_sign < 0 && set_point > 0) && i == 0) pwm_value = pwm_value * -1;
            if((pid_sign > 0 && set_point < 0) && i == 0) pwm_value = pwm_value * -1;

            iCm->setControlMode(joint_id, VOCAB_CM_PWM);
            iPwm->setRefDutyCycle(joint_id, pwm_value);

            yDebug() << pid_sign << " " << pwm_value;
        }
        
        //auto t0 = Time::now();
        auto t1{t0};
        done = false;
        double pid_ref, enc;
       

        while (!done) {
            data.t = Time::now() - t0;
            iPid->getPidReference(VOCAB_PIDTYPE_POSITION, joint_id, &data.pid_ref);
            iPid->getPidOutput(VOCAB_PIDTYPE_POSITION, joint_id, &data.pid_out);
            iEnc->getEncoder(joint_id, &data.enc);
            iCurr->getCurrent(joint_id, &data.curr);
            iMotorEnc->getMotorEncoder(joint_id, &data.motor_enc);
            iPwm->getDutyCycle(joint_id, &data.pwm_read);
            iTrq->getTorque(joint_id, &data.torque);


            data_vec.push_back(std::move(data));

            // auto& b = port.prepare();
            // b.clear();

            // b.addDouble(data.pid_ref);
            // b.addDouble(data.enc);

            // b.addDouble(data.pid_out);
            // b.addDouble(data.curr);

            // port.writeStrict();

            if (Time::now() - t1 >= time_delay) {
                
                if (control_mode == "position") iPos->checkMotionDone(joint_id, &done);
                else if(control_mode == "pwm"){

                    if(set_point > 0){

                        if(data.enc > set_point){
                            //yDebug() << data.enc << " " << set_point << " " << pwm_value; 
                            iPwm->setRefDutyCycle(joint_id, 0);
                            pwm_value = pwm_value * -1;
                            //Time::delay(pause);
                            done = true; 
                            }
                    } 
                    else if(data.enc < set_point){
                        //yDebug() << "OK" << " " << data.enc << " " << set_point << " " << pwm_value; 
                        iPwm->setRefDutyCycle(joint_id, 0); 
                        pwm_value = pwm_value * -1;
                        //Time::delay(pause);
                        done = true; 
                        }
                } 
                t1 = Time::now();
            }
            Time::delay(time_delay);
            
        }
        yDebug() << "OK! reached :" << " " << data.enc << " set-point : " << set_point;
        for(int k=0; k < pause * (1/time_delay); k++){
            data.t = Time::now() - t0;
            iPid->getPidReference(VOCAB_PIDTYPE_POSITION, joint_id, &data.pid_ref);
            iPid->getPidOutput(VOCAB_PIDTYPE_POSITION, joint_id, &data.pid_out);
            iEnc->getEncoder(joint_id, &data.enc);
            iCurr->getCurrent(joint_id, &data.curr);
            iMotorEnc->getMotorEncoder(joint_id, &data.motor_enc);
            iPwm->getDutyCycle(joint_id, &data.pwm_read);
            iTrq->getTorque(joint_id, &data.torque);


            data_vec.push_back(std::move(data));
            Time::delay(time_delay);

        }
  
    }

    // port.close();

    for (const auto& d : data_vec) {
        file << d.t << " " << d.pid_ref << " "
             << d.pid_out << " " << d.enc << " "
             << d.curr << " " << d.motor_enc << " "
             << d.pwm_read << " " << d.torque << std::endl;
    }

    // Homing
     iCm->setControlMode(joint_id, VOCAB_CM_POSITION);
     iPos->setRefSpeed(joint_id, 25.);
     iPos->setRefAcceleration(joint_id, std::numeric_limits<double>::max());
     iPos->positionMove(joint_id, 0.);
     while (!done) {
         iPos->checkMotionDone(joint_id, &done);
         Time::yield();
     }
    
    m_driver.close();
    file.close();

    yInfo()<<"Main returning...";
    return EXIT_SUCCESS;
}