
# Project 1: Build My World

![Screenshot](VirtualBox_vm_23_08_2020_18_18_39.png)

## Build Instructions
1. Make sure you have the following installed:
   - [ROS](http://wiki.ros.org/ROS/Installation)
   - Cmake
   - gcc/g++
   - Git
2. Clone the project
3. Go to the project folder
4. Create a build folder `mkdir build && cd build`
5. Build with cmake `cmake .. && make`
6. Add the build folder to the Gazebo plugin path: 
`GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:<path_to_build_folder>`. For example,
`GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:/home/RoboND-Build-My-World/build`
7. Go back to the project folder
8. Launch Gazebo world `gazebo world/UdacityOffice`

## Structure
```
.RoboND-Build-My-World             # Build My World Project 
├── robot                          # Model files 
│   ├── model
│   │   ├── mybuild
|   |   |   ├── model.config
│   │   |   ├── model.sdf
│   │   ├── myrobot
|   |   |   ├── model.config
│   │   |   ├── model.sdf
├── script                         # Plugin files 
│   ├── welcome.cpp
├── world                          # World files
│   ├── myworld
├── CMakeLists.txt
└──   
```
