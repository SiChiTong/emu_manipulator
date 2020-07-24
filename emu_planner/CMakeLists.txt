cmake_minimum_required(VERSION 3.1.3)
project(emu_planner)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  trajectory_msgs
  sensor_msgs
  message_generation
  emu_planner
)

#add_service_files(
#  FILES 
#  EmuPlanner.srv
#  )

#generate_messages(
#  DEPENDENCIES
#  std_msgs
#  trajectory_msgs
#  sensor_msgs
#  geometry_msgs
#  emu_planner
#)

catkin_package()

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
