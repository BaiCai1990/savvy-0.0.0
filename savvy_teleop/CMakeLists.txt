cmake_minimum_required(VERSION 2.8.3)
project(savvy_teleop)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES savvy_teleop
#  CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(teleop_node src/savvy_teleop_node.cpp)

target_link_libraries(teleop_node ${catkin_LIBRARIES})

add_dependencies(teleop_node savvy_teleop_generate_messages_cpp)


