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
#include <yarp/os/Os.h>
#include <yarp/sig/Vector.h>
#include <yarp/sig/Matrix.h>
#include <yarp/math/Math.h>
#include <iCub/ctrl/math.h>
#include <iCub/iKin/iKinFwd.h>

/******************************************************************************/
class iCubEyeNew : public iCub::iKin::iKinLimb {
protected:
    /**************************************************************************/
    void allocate(const std::string &_type) override {
        std::string eye = getType();
        yarp::sig::Matrix H0(4,4);
        H0.zero();
        H0(0,1) = -1.0;
        H0(1,2) = -1.0;
        H0(2,0) = 1.0;
        H0(3,3) = 1.0;
        setH0(H0);

        if (eye == "right") {
            pushLink(new iCub::iKin::iKinLink(  0.032,     0.0,  M_PI/2.0,       0.0, -22.0*iCub::ctrl::CTRL_DEG2RAD, 84.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink(    0.0, -0.0055,  M_PI/2.0, -M_PI/2.0, -39.0*iCub::ctrl::CTRL_DEG2RAD, 39.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink(    0.0, -0.2233, -M_PI/2.0, -M_PI/2.0, -59.0*iCub::ctrl::CTRL_DEG2RAD, 59.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink( 0.0095,     0.0,  M_PI/2.0,  M_PI/2.0, -40.0*iCub::ctrl::CTRL_DEG2RAD, 30.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink(    0.0,     0.0, -M_PI/2.0, -M_PI/2.0, -70.0*iCub::ctrl::CTRL_DEG2RAD, 60.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink(-0.0509, 0.08205, -M_PI/2.0,  M_PI/2.0, -55.0*iCub::ctrl::CTRL_DEG2RAD, 55.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink(    0.0,   0.034, -M_PI/2.0,       0.0, -35.0*iCub::ctrl::CTRL_DEG2RAD, 15.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink(    0.0,     0.0,  M_PI/2.0, -M_PI/2.0, -50.0*iCub::ctrl::CTRL_DEG2RAD, 50.0*iCub::ctrl::CTRL_DEG2RAD));
        } else {  // left
            pushLink(new iCub::iKin::iKinLink(  0.032,     0.0,  M_PI/2.0,       0.0, -22.0*iCub::ctrl::CTRL_DEG2RAD, 84.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink(    0.0, -0.0055,  M_PI/2.0, -M_PI/2.0, -39.0*iCub::ctrl::CTRL_DEG2RAD, 39.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink(    0.0, -0.2233, -M_PI/2.0, -M_PI/2.0, -59.0*iCub::ctrl::CTRL_DEG2RAD, 59.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink( 0.0095,     0.0,  M_PI/2.0,  M_PI/2.0, -40.0*iCub::ctrl::CTRL_DEG2RAD, 30.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink(    0.0,     0.0, -M_PI/2.0, -M_PI/2.0, -70.0*iCub::ctrl::CTRL_DEG2RAD, 60.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink(-0.0509, 0.08205, -M_PI/2.0,  M_PI/2.0, -55.0*iCub::ctrl::CTRL_DEG2RAD, 55.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink(    0.0,  -0.034, -M_PI/2.0,       0.0, -35.0*iCub::ctrl::CTRL_DEG2RAD, 15.0*iCub::ctrl::CTRL_DEG2RAD));
            pushLink(new iCub::iKin::iKinLink(    0.0,     0.0,  M_PI/2.0, -M_PI/2.0, -50.0*iCub::ctrl::CTRL_DEG2RAD, 50.0*iCub::ctrl::CTRL_DEG2RAD));
        }
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
    rf.setDefaultContext("fkin");
    rf.configure(argc, argv);

    if (rf.check("help")) {
        std::cout << "- Options:" << std::endl;
        std::cout << "--type [left|right]" << std::endl;
        std::cout << "--joints \"(0.0 0.0 ... 0.0)\" - (deg)" << std::endl;
        std::cout << "- Example:" << std::endl;
        std::cout << "./fkin --type right --joints \"(1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0)\"" << std::endl;
        return EXIT_SUCCESS;
    }
    
    auto type = rf.check("type", yarp::os::Value("right")).asString();
    auto eye = std::make_unique<iCubEyeNew>(type);
    eye->setAng(yarp::math::zeros(eye->getDOF()));

    if (rf.check("joints")) {
        if (const auto* joints = rf.find("joints").asList()) {
            size_t len = std::min((size_t)eye->getDOF(), joints->size());
            for (size_t i = 0; i < len; i++) {
                eye->setAng(i, iCub::ctrl::CTRL_DEG2RAD * joints->get(i).asDouble());
            }
        }
    }

    std::cout << "- type" << std::endl << eye->getType() << std::endl;
    std::cout << "- joints" << std::endl << (iCub::ctrl::CTRL_RAD2DEG * eye->getAng()).toString(5, 5) << std::endl;
    std::cout << "- H" << std::endl << eye->getH().toString(5, 5) << std::endl;
    
    yarp::os::mkdir_p(rf.getHomeContextPath().c_str());
    std::string filename(rf.getHomeContextPath() + "/frames.obj");
    std::ofstream fout(filename);
    if (fout.is_open()) {
        std::cout << "Saving frames to file \"" << filename << "\"..." << std::endl;
        fout << "# Vertices" << std::endl;
        for (size_t v = 0; v < eye->getDOF(); v++) {
            auto p = eye->getH(v).getCol(3).subVector(0, 2);
            fout << "v " << p.toString(5, 5) << std::endl;
        }
        auto Hee = eye->getH();
        auto xee = Hee.getCol(0).subVector(0, 2);
        auto yee = Hee.getCol(1).subVector(0, 2);
        auto pee = Hee.getCol(3).subVector(0, 2);
        auto l2 = .02;
        fout << "v " << (pee + l2 * xee + l2 * yee).toString(5, 5) << std::endl;
        fout << "v " << (pee + l2 * xee - l2 * yee).toString(5, 5) << std::endl;
        fout << "v " << (pee - l2 * xee + l2 * yee).toString(5, 5) << std::endl;
        fout << "v " << (pee - l2 * xee - l2 * yee).toString(5, 5) << std::endl;
        fout << "# Lines" << std::endl;
        for (size_t v = 0; v < eye->getDOF()-1; v++) {
            fout << "l " << v+1 << " " << v+2 << std::endl;
        }
        fout << "# Faces" << std::endl;
        auto dof = eye->getDOF();
        fout << "f " << dof+1 << " " << dof+2 << " " << dof+3 << " " << dof+4 << std::endl;
        std::cout << "...saved!" << std::endl;
        fout.close();
    } else {
        std::cerr << "Problems detected while saving frames to file!" << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}