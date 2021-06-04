/******************************************************************************
 *                                                                            *
 * Copyright (C) 2021 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

#include <cstdlib>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

#include <yarp/os/Value.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/ResourceFinder.h>
#include <yarp/sig/Vector.h>
#include <yarp/sig/Matrix.h>
#include <yarp/math/Math.h>
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
    yarp::os::ResourceFinder rf;
    rf.configure(argc, argv);

    if (rf.check("help")) {
        std::cout << "- Options:" << std::endl;
        std::cout << "--version [left|right]_x.y" << std::endl;
        std::cout << "--joints \"(0.0 0.0 ... 0.0)\" - (deg)" << std::endl;
        std::cout << "- Example:" << std::endl;
        std::cout << "./fkin --version right_2.8 --joints \"(1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0)\"" << std::endl;
        return EXIT_SUCCESS;
    }
    
    auto version = rf.check("version", yarp::os::Value("right_2.8")).asString();
    auto eye = std::make_unique<iCubEyeNew>(version);
    eye->releaseLink(0);
    eye->releaseLink(1);
    eye->releaseLink(2);
    eye->setAng(yarp::math::zeros(eye->getDOF()));

    if (rf.check("joints")) {
        if (const auto* joints = rf.find("joints").asList()) {
            size_t len = std::min((size_t)eye->getDOF(), joints->size());
            for (size_t i = 0; i < len; i++) {
                eye->setAng(i, iCub::ctrl::CTRL_DEG2RAD * joints->get(i).asDouble());
            }
        }
    }

    std::cout << "- version" << std::endl << eye->getType() << std::endl;
    std::cout << "- joints" << std::endl << (iCub::ctrl::CTRL_RAD2DEG * eye->getAng()).toString(5, 5) << std::endl;
    std::cout << "- H" << std::endl << eye->getH().toString(5, 5) << std::endl;
    
    std::ofstream fout("frames.log");
    if (fout.is_open()) {
        std::cout << "Saving frames to file \"frames.log\"..." << std::endl;
        for (size_t i = 0; i < eye->getDOF(); i++) {
            auto H = eye->getH(i);
            for (size_t j = 0; j < H.rows(); j++) {
                fout << H.getRow(j).toString(5, 5) << " ";
            }
            fout << std::endl;
        }
        std::cout << "...saved!" << std::endl;
    } else {
        std::cerr << "Problems detected while saving frames to file!" << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}