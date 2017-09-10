// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __SEGMENTOR_THREAD_HPP__
#define __SEGMENTOR_THREAD_HPP__

#include <cstdio>

#include <yarp/os/Bottle.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/ConnectionReader.h>
#include <yarp/os/Port.h>
#include <yarp/os/PortReader.h>
#include <yarp/os/RateThread.h>
#include <yarp/os/ResourceFinder.h>

#include <yarp/dev/IOpenNI2DeviceDriver.h>

#include <yarp/sig/Image.h>

#include <opencv2/objdetect/objdetect.hpp>

// thanks! https://web.stanford.edu/~qianyizh/projects/scenedata.html
#define DEFAULT_FX_D          525.0  // 640x480
#define DEFAULT_FY_D          525.0  //
#define DEFAULT_CX_D          319.5  //
#define DEFAULT_CY_D          239.5  //

#define DEFAULT_RATE_MS 20
#define DEFAULT_SEE_BOUNDING 3
#define DEFAULT_THRESHOLD 55
#define DEFAULT_XMLCASCADE  "haarcascade_frontalface_alt.xml"

namespace roboticslab
{

/**
 * @ingroup haarDetection2D
 *
 * @brief Implements haarDetection2D callback on Bottle.
 */
class DataProcessor : public yarp::os::PortReader
{
private:
    virtual bool read(yarp::os::ConnectionReader& connection)
    {
        yarp::os::Bottle b;
        b.read(connection);

        // process data in b
        std::printf("Got %s\n", b.toString().c_str());

        if (waitForFirst)
        {
            xKeep = b.get(0).asInt();
            yKeep = b.get(1).asInt();
            waitForFirst = false;
        }
        else
        {
            if (b.get(0).asInt() < xKeep || b.get(1).asInt() < yKeep)
            {
                x = y = w = h = 0;
            }
            else
            {
                x = y = xKeep;
                w = b.get(0).asInt() - x;
                h = b.get(1).asInt() - y;
            }

            waitForFirst = true;
        }

        return true;
    }

public:
    bool reset()
    {
        waitForFirst = true;
        x = y = w = h = 0;
        xKeep = yKeep = 0;
        return true;
    }

    int xKeep, yKeep;
    int x, y, w, h;
    bool waitForFirst;
};

/**
 * @ingroup haarDetection2D
 *
 * @brief Implements haarDetection2D RateThread.
 */
class SegmentorThread : public yarp::os::RateThread
{
private:
    yarp::dev::IOpenNI2DeviceDriver *kinect;
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> > *pOutImg;  // for testing
    yarp::os::Port *pOutPort;

    double fx_d, fy_d, cx_d, cy_d;
    int cropSelector;

    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >* outCropSelectorImg;
    yarp::os::Port* inCropSelectorPort;

    DataProcessor processor;

    cv::CascadeClassifier face_cascade;

public:
    SegmentorThread() : RateThread(DEFAULT_RATE_MS) {}

    void setIKinectDeviceDriver(yarp::dev::IOpenNI2DeviceDriver * _kinect);
    void setOutImg(yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> > * _pOutImg);
    void setOutPort(yarp::os::Port *_pOutPort);
    void init(yarp::os::ResourceFinder &rf);
    void run();  // The periodical function

    void setCropSelector(int cropSelector)
    {
        this->cropSelector = cropSelector;
    }

    void setOutCropSelectorImg(yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >* outCropSelectorImg)
    {
        this->outCropSelectorImg = outCropSelectorImg;
    }

    void setInCropSelectorPort(yarp::os::Port* inCropSelectorPort)
    {
        this->inCropSelectorPort = inCropSelectorPort;
    }
};

}  // namespace roboticslab

#endif  // __SEGMENTOR_THREAD_HPP__
