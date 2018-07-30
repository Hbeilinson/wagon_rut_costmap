# wagon_rut_costmap

This repository contains code to convert a ROS Costmap 2D into a gridmap, and then save it as a pgm image, using the ETHZ ASL gridmap package (https://github.com/ethz-asl/grid_map). It requires the simple_costmap_layer respository. The code to perform the conversions can be found in convert_to_grid.cpp.

In order to use the gridmap package make sure to include the header files for each sub-package and provide these sub-packages as dependencies, rather than the wrapper grid_map package. In addition, it's necessary to compile with C++ 11. 

To use the CV converter specifically, you must provide a CV encoding. The final digit in the encoding represents the number of channels. It must match the second parameter in the bracketed type. For further examples see the tests for the grid_map CV converter: https://github.com/ethz-asl/grid_map/blob/master/grid_map_cv/test/GridMapCvTest.cpp

For my actual code for the wagon rut costmap, please see https://github.com/OSUrobotics/wagon_rut_costmap.

