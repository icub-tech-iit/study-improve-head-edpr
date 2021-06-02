/******************************************************************************
 *                                                                            *
 * Copyright (C) 2021 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <string>

#include <yarp/sig/Vector.h>
#include <yarp/sig/Matrix.h>
#include <iCub/ctrl/math.h>
#include <iCub/iKin/iKinFwd.h>

/******************************************************************************/
class iCubEyeNew : public iCub::iKin::iKinLimb {
protected:
    double version;

    /**************************************************************************/
    void allocate(const std::string &_type) override {
        std::string eye;
        size_t underscore = getType().find('_');
        if (underscore != std::string::npos) {
            eye = getType().substr(0, underscore);
            version = std::strtod(getType().substr(underscore+2).c_str(), nullptr);
        } else {
            eye=getType();
            version=1.0;
        }

        yarp::sig::Matrix H0(4,4);
        H0.zero();
        H0(0,1) = -1.0;
        H0(1,2) = -1.0;
        H0(2,0) = 1.0;
        H0(3,3) = 1.0;
        setH0(H0);

        if (eye == "right") {
            if (version < 2.0) {
                pushLink(new iCub::iKin::iKinLink(  0.032,     0.0,  M_PI/2.0,       0.0, -22.0*iCub::ctrl::CTRL_DEG2RAD, 84.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0, -0.0055,  M_PI/2.0, -M_PI/2.0, -39.0*iCub::ctrl::CTRL_DEG2RAD, 39.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(0.00231, -0.1933, -M_PI/2.0, -M_PI/2.0, -59.0*iCub::ctrl::CTRL_DEG2RAD, 59.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(  0.033,     0.0,  M_PI/2.0,  M_PI/2.0, -40.0*iCub::ctrl::CTRL_DEG2RAD, 30.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0,   0.001, -M_PI/2.0, -M_PI/2.0, -70.0*iCub::ctrl::CTRL_DEG2RAD, 60.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink( -0.054,  0.0825, -M_PI/2.0,  M_PI/2.0, -55.0*iCub::ctrl::CTRL_DEG2RAD, 55.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0,   0.034, -M_PI/2.0,       0.0, -35.0*iCub::ctrl::CTRL_DEG2RAD, 15.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0,     0.0,  M_PI/2.0, -M_PI/2.0, -50.0*iCub::ctrl::CTRL_DEG2RAD, 50.0*iCub::ctrl::CTRL_DEG2RAD));
            } else if (version < 3.0) {
                pushLink(new iCub::iKin::iKinLink(  0.032,     0.0,  M_PI/2.0,       0.0, -22.0*iCub::ctrl::CTRL_DEG2RAD, 84.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0, -0.0055,  M_PI/2.0, -M_PI/2.0, -39.0*iCub::ctrl::CTRL_DEG2RAD, 39.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0, -0.2233, -M_PI/2.0, -M_PI/2.0, -59.0*iCub::ctrl::CTRL_DEG2RAD, 59.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink( 0.0095,     0.0,  M_PI/2.0,  M_PI/2.0, -40.0*iCub::ctrl::CTRL_DEG2RAD, 30.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0,     0.0, -M_PI/2.0, -M_PI/2.0, -70.0*iCub::ctrl::CTRL_DEG2RAD, 60.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(-0.0509, 0.08205, -M_PI/2.0,  M_PI/2.0, -55.0*iCub::ctrl::CTRL_DEG2RAD, 55.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0,   0.034, -M_PI/2.0,       0.0, -35.0*iCub::ctrl::CTRL_DEG2RAD, 15.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0,     0.0,  M_PI/2.0, -M_PI/2.0, -50.0*iCub::ctrl::CTRL_DEG2RAD, 50.0*iCub::ctrl::CTRL_DEG2RAD));
            } else {  // version >= 3.0
                H0.zero();
                H0(0,2) = 1.0;
                H0(1,1) = -1.0;
                H0(2,0) = 1.0;
                H0(3,3) = 1.0;
                setH0(H0);

                pushLink(new iCub::iKin::iKinLink(     0.0725,       0.0, -M_PI/2.0,       0.0, -20.0*iCub::ctrl::CTRL_DEG2RAD, 20.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(        0.0,       0.0,  M_PI/2.0, -M_PI/2.0, -15.0*iCub::ctrl::CTRL_DEG2RAD, 40.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(-0.00486151,  -0.26377, -M_PI/2.0,      M_PI, -40.0*iCub::ctrl::CTRL_DEG2RAD, 40.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(     0.0095,       0.0,  M_PI/2.0,  M_PI/2.0, -30.0*iCub::ctrl::CTRL_DEG2RAD, 22.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(        0.0,       0.0, -M_PI/2.0, -M_PI/2.0, -20.0*iCub::ctrl::CTRL_DEG2RAD, 20.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    -0.0509,   0.08205, -M_PI/2.0,  M_PI/2.0, -45.0*iCub::ctrl::CTRL_DEG2RAD, 45.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(        0.0,     0.034, -M_PI/2.0,       0.0, -35.0*iCub::ctrl::CTRL_DEG2RAD, 15.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(        0.0,       0.0,  M_PI/2.0, -M_PI/2.0, -50.0*iCub::ctrl::CTRL_DEG2RAD, 50.0*iCub::ctrl::CTRL_DEG2RAD));
            }
        } else {  // left
            if (version < 2.0) {
                pushLink(new iCub::iKin::iKinLink(  0.032,     0.0,  M_PI/2.0,       0.0, -22.0*iCub::ctrl::CTRL_DEG2RAD, 84.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0, -0.0055,  M_PI/2.0, -M_PI/2.0, -39.0*iCub::ctrl::CTRL_DEG2RAD, 39.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(0.00231, -0.1933, -M_PI/2.0, -M_PI/2.0, -59.0*iCub::ctrl::CTRL_DEG2RAD, 59.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(  0.033,     0.0,  M_PI/2.0,  M_PI/2.0, -40.0*iCub::ctrl::CTRL_DEG2RAD, 30.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0,   0.001, -M_PI/2.0, -M_PI/2.0, -70.0*iCub::ctrl::CTRL_DEG2RAD, 60.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink( -0.054,  0.0825, -M_PI/2.0,  M_PI/2.0, -55.0*iCub::ctrl::CTRL_DEG2RAD, 55.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0,  -0.034, -M_PI/2.0,       0.0, -35.0*iCub::ctrl::CTRL_DEG2RAD, 15.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0,     0.0,  M_PI/2.0, -M_PI/2.0, -50.0*iCub::ctrl::CTRL_DEG2RAD, 50.0*iCub::ctrl::CTRL_DEG2RAD));
            } else if (version < 3.0) {
                pushLink(new iCub::iKin::iKinLink(  0.032,     0.0,  M_PI/2.0,       0.0, -22.0*iCub::ctrl::CTRL_DEG2RAD, 84.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0, -0.0055,  M_PI/2.0, -M_PI/2.0, -39.0*iCub::ctrl::CTRL_DEG2RAD, 39.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0, -0.2233, -M_PI/2.0, -M_PI/2.0, -59.0*iCub::ctrl::CTRL_DEG2RAD, 59.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink( 0.0095,     0.0,  M_PI/2.0,  M_PI/2.0, -40.0*iCub::ctrl::CTRL_DEG2RAD, 30.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0,     0.0, -M_PI/2.0, -M_PI/2.0, -70.0*iCub::ctrl::CTRL_DEG2RAD, 60.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(-0.0509, 0.08205, -M_PI/2.0,  M_PI/2.0, -55.0*iCub::ctrl::CTRL_DEG2RAD, 55.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0,  -0.034, -M_PI/2.0,       0.0, -35.0*iCub::ctrl::CTRL_DEG2RAD, 15.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    0.0,     0.0,  M_PI/2.0, -M_PI/2.0, -50.0*iCub::ctrl::CTRL_DEG2RAD, 50.0*iCub::ctrl::CTRL_DEG2RAD));
            } else {  // version >= 3.0
                H0.zero();
                H0(0,2) = 1.0;
                H0(1,1) = -1.0;
                H0(2,0) = 1.0;
                H0(3,3) = 1.0;
                setH0(H0);

                pushLink(new iCub::iKin::iKinLink(     0.0725,      0.0, -M_PI/2.0,       0.0, -20.0*iCub::ctrl::CTRL_DEG2RAD, 20.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(        0.0,      0.0,  M_PI/2.0, -M_PI/2.0, -15.0*iCub::ctrl::CTRL_DEG2RAD, 40.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(-0.00486151, -0.26377, -M_PI/2.0,      M_PI, -40.0*iCub::ctrl::CTRL_DEG2RAD, 40.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(     0.0095,      0.0,  M_PI/2.0,  M_PI/2.0, -30.0*iCub::ctrl::CTRL_DEG2RAD, 22.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(        0.0,      0.0, -M_PI/2.0, -M_PI/2.0, -20.0*iCub::ctrl::CTRL_DEG2RAD, 20.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(    -0.0509,  0.08205, -M_PI/2.0,  M_PI/2.0, -45.0*iCub::ctrl::CTRL_DEG2RAD, 45.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(        0.0,   -0.034, -M_PI/2.0,       0.0, -35.0*iCub::ctrl::CTRL_DEG2RAD, 15.0*iCub::ctrl::CTRL_DEG2RAD));
                pushLink(new iCub::iKin::iKinLink(        0.0,      0.0,  M_PI/2.0, -M_PI/2.0, -50.0*iCub::ctrl::CTRL_DEG2RAD, 50.0*iCub::ctrl::CTRL_DEG2RAD));
            }
        }

        blockLink(0, 0.0);
        blockLink(1, 0.0);
        blockLink(2, 0.0);
    }

public:
    /**************************************************************************/
    iCubEyeNew() : iCub::iKin::iKinLimb(std::string("right")) {
        allocate(getType());
    }

    /**************************************************************************/
    iCubEyeNew(const std::string &_type) : iCub::iKin::iKinLimb(_type) {
        allocate(_type);
    }
};


/******************************************************************************/
int main(int argc, char* argv[]) {
    return EXIT_SUCCESS;
}