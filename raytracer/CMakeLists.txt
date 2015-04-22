cmake_minimum_required( VERSION 2.8 )

project( GTRenderer )

set( CMAKE_BUILD_TYPE "RELEASE" )

#FIND_PACKAGE(Qt4 REQUIRED)

#include( ${QT_USE_FILE} )
#add_definitions( ${QT_DEFINITIONS} )

set (CMAKE_CXX_FLAGS "-Wall -pthread -std=c++11 -Wl,--no-as-needed")
add_definitions(${CMAKE_CXX_FLAGS})

#add_definitions( "-std=c++11" )
#add_definitions( "-DQT_GUI_LIB" )
#add_definitions( "-Wl" )
#add_definitions( "--no-as-needed" )
#add_definitions( "-pthread" )

#find_package(OpenMP)
#if (OPENMP_FOUND)
#    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#endif()

include_directories( include . )

add_library( RayTracer	Vector3.cpp
								Camera.cpp
								Material.cpp
								Primitive.cpp
								Sphere.cpp
								Box.cpp
								Ray.cpp
								KDTree.cpp
								LightSource.cpp
								PointLight.cpp
								DirectionLight.cpp
								IntersectionInfo.cpp
								Scene.cpp
								SceneLoader.cpp
								Renderer.cpp
								RayTracer.cpp
								OCTracer.cpp
								main.cpp
								GTRenderer.cpp )

add_executable( GTRenderer main.cpp )
#target_link_libraries( GTRenderer RayTracer ${QT_LIBRARIES} )
target_link_libraries( GTRenderer RayTracer )
