cmake_minimum_required(VERSION 3.0.2)
project(robosys_pkg)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  rospy
  sensor_msgs
  std_msgs
)

find_package(OpenCV REQUIRED)

catkin_package(
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp
  DEPENDS
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}  
)

add_executable(imgsub src/imgsub.cpp)
target_link_libraries(imgsub ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})