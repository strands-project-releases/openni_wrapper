cmake_minimum_required(VERSION 2.8.3)
project(openni_wrapper)

set(CMAKE_CXX_FLAGS "-g -fPIC -std=c++0x -fpermissive")

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs cv_bridge nodelet class_loader image_proc depth_image_proc)
find_package(OpenCV REQUIRED )

set(OPENNI2.2_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(OPENNI2.2_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/OpenNI2/)

link_directories(${OPENNI2.2_DIR}/OpenNI2/Bin/x64-Release)
link_directories(OpenNI2/Bin/x64-Release)

include_directories(${OPENNI2.2_DIR}/OpenNI2/Include)

catkin_package(
   INCLUDE_DIRS include
   CATKIN_DEPENDS roscpp rospy std_msgs cv_bridge nodelet class_loader image_proc depth_image_proc
   DEPENDS libudev-dev libopencv-dev libusb-1.0-dev glut
)

include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${OPENNI2.2_DIR}
)


set(HDRS
    include/ColorCallback.h
    include/OpenniWrapperNodelet.h
    include/DepthCallback.h
    include/OpenniWrapperNode.h
)

set(SRCS
    src/ColorCallback.cpp
    src/OpenniWrapperNodelet.cpp
    src/DepthCallback.cpp
    src/OpenniWrapperNode.cpp
    src/main.cpp
)

add_executable(openni_wrapper ${HDRS} ${SRCS})

add_library(openni_wrapper_lib  ${HDRS} ${SRCS})

 target_link_libraries(openni_wrapper
   ${catkin_LIBRARIES} OpenNI2 ${OpenCV_LIBS}
 )

 target_link_libraries(openni_wrapper_lib
   ${catkin_LIBRARIES} OpenNI2 ${OpenCV_LIBS}
 )

add_dependencies(openni_wrapper openni_wrapper_lib)

add_custom_command(TARGET openni_wrapper_lib PRE_LINK COMMAND make ARGS -j2 WORKING_DIRECTORY ${OPENNI2.2_BUILD_DIR} COMMENT "Compiling Openni2.2. This could take some time.")

############## OPENNI_WRAPPER installation ###################

install(TARGETS openni_wrapper_lib openni_wrapper 
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)

install(FILES nodelet_plugins.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

############## OPENNI2 installation ###################

install(DIRECTORY ${OPENNI2.2_DIR}/OpenNI2/Include/.
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}/OpenNI2/Include
)

install(DIRECTORY ${OPENNI2.2_DIR}/OpenNI2/Bin/x64-Release/.
  DESTINATION ${CATKIN_GLOBAL_LIB_DESTINATION}
)
