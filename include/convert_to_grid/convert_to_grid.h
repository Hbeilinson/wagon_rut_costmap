#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include "grid_map_ros/GridMapRosConverter.hpp"
#include <grid_map_msgs/GridMap.h>
// #include <iostream>

#include "nav_msgs/OccupancyGrid.h"

#include <grid_map_cv/GridMapCvConverter.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

using namespace std;
using namespace grid_map;
using namespace cv;


class ConvertToGrid
{
  public:
    ros::Subscriber costmap_sub;
    ros::Publisher gridmap_pub;
    ConvertToGrid();
    void costmap_callback(const nav_msgs::OccupancyGrid& costmap);
    GridMap map;
    // cv::Mat& image;
};
