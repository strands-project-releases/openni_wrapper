#ifndef __OPENNI_WRAPPER_NODE__
#define __OPENNI_WRAPPER_NODE__

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <OpenNI2/Include/OpenNI.h>
#include "ColorCallback.h"
#include "DepthCallback.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

 #include "ros/ros.h"
class OpenNIDeviceListener : public openni::OpenNI::DeviceConnectedListener,
                                    public openni::OpenNI::DeviceDisconnectedListener,
                                    public openni::OpenNI::DeviceStateChangedListener
{
public:
    virtual void onDeviceStateChanged(const openni::DeviceInfo* pInfo, openni::DeviceState state)
    {
        printf("Device \"%s\" error state changed to %d\n", pInfo->getUri(), state);
    }

    virtual void onDeviceConnected(const openni::DeviceInfo* pInfo)
    {
        printf("Device \"%s\" connected\n", pInfo->getUri());
    }

    virtual void onDeviceDisconnected(const openni::DeviceInfo* pInfo)
    {
        printf("Device \"%s\" disconnected\n", pInfo->getUri());
    }
};


class OpenniWrapperNode
{
public:
    OpenniWrapperNode(ros::NodeHandle nh, ros::NodeHandle private_nh);
    ~OpenniWrapperNode();

    void initializeOpenni();
    void terminateOpenni();

private:
    ros::NodeHandle m_nodeHandle;
    ros::NodeHandle m_privateNodeHandle;

    OpenNIDeviceListener m_devicePrinter;
    std::vector<openni::Device*> m_vDevice;
    std::vector<openni::VideoStream*> m_vColor;
    std::vector<openni::VideoStream*> m_vDepth;
    std::vector<ColorCallback*>       m_vColorCallback;
    std::vector<DepthCallback*>       m_vDepthCallback;

    std::vector<std::string>         m_vCameraNamespace;
    int                              m_DevicesDefined;


    const static int          openni_wrapper_max_devices;

};


#endif
