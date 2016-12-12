cmake_minimum_required(VERSION 2.8.3)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")
project(projekt_przejsciowy)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
link_directories(${PROTUBUF_LIBRARY_DIRS})

find_package(Qt4)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

# Load catkin and all dependencies required for this package
find_package(catkin REQUIRED COMPONENTS 
  roscpp 
  gazebo_ros 
)

# Depend on system install of Gazebo
find_package(gazebo REQUIRED)

link_directories(${GAZEBO_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED src/world_plugin.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES} ${PROTOBUF_LIBRARIES})


QT4_WRAP_CPP(headers_MOC src/SimulationGUI.hh src/WorldConfigurationWindow.hh src/RobotManagementWindow.hh src/RobotManagementTab.hh src/ResultsWindow.hh src/qcustomplot.h)
add_library(_simulation_gui_plugin SHARED ${headers_MOC} src/SimulationGUI.cc src/WorldConfigurationWindow.cc src/RobotManagementWindow.cc src/RobotManagementTab.cc src/ResultsWindow.cc src/qcustomplot.cpp)
target_link_libraries(_simulation_gui_plugin
   ${GAZEBO_LIBRARIES}
   ${QT_LIBRARIES}
   ${PROTOBUF_LIBRARIES}
)

catkin_package(
  DEPENDS 
    roscpp 
    gazebo_ros 
)
