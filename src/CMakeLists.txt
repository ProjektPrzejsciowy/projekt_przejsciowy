cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
link_directories(${PROTUBUF_LIBRARY_DIRS})

find_package(GAZEBO)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

find_package(Qt4)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

QT4_WRAP_CPP(headers_MOC WorldControl.hh)
add_library(_world_control_plugin SHARED ${headers_MOC} WorldControl.cc)
target_link_libraries(_world_control_plugin
   ${GAZEBO_LIBRARIES}
   ${QT_LIBRARIES}
   ${PROTOBUF_LIBRARIES}
)


QT4_WRAP_CPP(headers_MOC SimulationGUI.hh WorldConfigurationWindow.hh RobotManagementWindow.hh ResultsWindow.hh qcustomplot.h)
add_library(_simulation_gui_plugin SHARED ${headers_MOC} SimulationGUI.cc WorldConfigurationWindow.cc RobotManagementWindow.cc ResultsWindow.cc qcustomplot.cpp)
target_link_libraries(_simulation_gui_plugin
   ${GAZEBO_LIBRARIES}
   ${QT_LIBRARIES}
   ${PROTOBUF_LIBRARIES}
)
