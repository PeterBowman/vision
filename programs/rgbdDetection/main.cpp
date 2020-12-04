// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/**
 *
 * @ingroup vision_programs
 *
 * \defgroup rgbdDetection rgbdDetection
 *
 * @brief Creates an instance of roboticslab::RgbdDetection.
 *
 * @section rgbdDetectionOptions RgbdDetection options:
 *
 * |PROPERTY            | DESCRIPTION                           | DEFAULT              |
 * |--------------------|---------------------------------------|----------------------|
 * |help                |                                       |                      |
 * |from                |file.ini                               |                      |
 * |context             |path                                   |                      |
 * |cropSelector        |                                       |0                     |
 * |RGBDDevice          |device we create                       |RGBDSensorClient      |
 * |RGBDLocal           |if accesing remote, local port name    |/rgbdDetection        |
 * |RGBDRemote          |if accesing remote, remote port name   |/rgbd                 |
 * |watchdog            |                                       |2.000000              |
 *
 *
 * @section  rgbdDetectionPorts RgbdDetection output ports:
 * |OUTPUT PORT            | CONTENT   |
 * |-----------------------|-----------|
 * |/rgbdDetection/img:o   | Output RGBD image with face detection using squares  |
 * |/rgbdDetection/state:o | xyz coordinates of face detection                    |
 *
 * @section segmentorThread SegmentorThread options:
 *
 * |PROPERTY            | DESCRIPTION                           | DEFAULT                       |
 * |--------------------|---------------------------------------|-------------------------------|
 * |help                |                                       |                               |
 * |from                |file.ini                               |                               |
 * |context             |path                                   |                               |
 * |rateMs              |                                       |20                             |
 * |xmlCascade          |file.xml                               |switchcascade_frontalface_alt.xml|
 *
 *
 *
 *


*/

#include "RgbdDetection.hpp"

int main(int argc, char** argv) {

    yarp::os::ResourceFinder rf;
    rf.setVerbose(true);
    rf.setDefaultContext("rgbdDetection");
    rf.setDefaultConfigFile("rgbdDetection.ini");
    rf.configure(argc, argv);

    roboticslab::RgbdDetection mod;
    if(rf.check("help")) {
        return mod.runModule(rf);
    }

    printf("Run \"%s --help\" for options.\n",argv[0]);
    printf("%s checking for yarp network... ",argv[0]);
    fflush(stdout);
    yarp::os::Network yarp;
    if (!yarp.checkNetwork()) {
        fprintf(stderr,"[fail]\n%s found no yarp network (try running \"yarpserver &\"), bye!\n",argv[0]);
        return 1;
    } else printf("[ok]\n");

    return mod.runModule(rf);
}
