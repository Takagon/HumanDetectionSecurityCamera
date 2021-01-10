#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/Int32.h>
#include <vector>

static const int LOOPRATE = 1;

cv::CascadeClassifier cascade;

cv::Mat CamImg, FaceImg;
int globalfaceflag = 0;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    //cascade.load("/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml");
    //cascade.load("/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml");
    //cascade.load("/usr/share/opencv/haarcascades/haarcascade_frontalface_alt2.xml");
    cascade.load("/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml");
    CamImg = cv_bridge::toCvShare(msg, "bgr8")->image;
    std::vector<cv::Rect> faces;
    cascade.detectMultiScale(CamImg, faces, 1.1, 3, 0, cv::Size(20,20));
    for (size_t i = 0; i < (globalfaceflag = faces.size()); i++){
        rectangle(CamImg, cv::Point(faces[i].x, faces[i].y), cv::Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), cv::Scalar(0, 0, 255), 3);
        FaceImg = cv::Mat(CamImg, cv::Rect(faces[i].x,faces[i].y,faces[i].width,faces[i].height)); 
    }
    imwrite("/home/takagon/robosys_ws/src/robosys_pkg/src/faceimages/face_dst.jpg",FaceImg);
    ROS_INFO("faceflag is %d",globalfaceflag);
    cv::imshow("view", CamImg);
    cv::waitKey(2);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;

  cv::namedWindow("view");

  //face exist flag publish define
  ros::Publisher pub = nh.advertise<std_msgs::Int32>("faceflag", 1000);

  //camera image subscribe define
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("cv_camera/image_raw", 1, imageCallback);

  ros::Rate loop_rate(LOOPRATE);
  while (ros::ok())
  {
    std_msgs::Int32 faceflag;
    faceflag.data = globalfaceflag;
    pub.publish(faceflag);
    ros::spinOnce();
    loop_rate.sleep();
  }
  
  cv::destroyWindow("view");
}
