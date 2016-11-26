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

QT4_WRAP_CPP(headers_MOC world_plugin.hh)
add_library(world_plugin SHARED ${headers_MOC} world_plugin.cc)
target_link_libraries(world_plugin
   ${GAZEBO_LIBRARIES}
   ${OGRE_LIBRARIES}
   ${OGRE-Terrain_LIBRARIES}
   ${QT_LIBRARIES}
   ${PROTOBUF_LIBRARIES}
)

QT4_WRAP_CPP(headers_MOC pp_gazebo_plugin.hh)
add_library(pp_gazebo_plugin SHARED ${headers_MOC} pp_gazebo_plugin.cc)
target_link_libraries(pp_gazebo_plugin
   ${GAZEBO_LIBRARIES}
   ${OGRE_LIBRARIES}
   ${OGRE-Terrain_LIBRARIES}
   ${QT_LIBRARIES}
   ${PROTOBUF_LIBRARIES}
)
