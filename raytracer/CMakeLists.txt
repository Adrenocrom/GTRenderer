cmake_minimum_required( VERSION 2.6 )

project( GTRenderer )

set( CMAKE_BUILD_TYPE "RELEASE" )

FIND_PACKAGE(Qt4 REQUIRED)

include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )

add_definitions( "-std=c++11" )

include_directories( include . )

add_library( RayTracer	Vector3.cpp
								Camera.cpp
								Sphere.cpp
								Ray.cpp
								LightSource.cpp
								Scene.cpp
								Renderer.cpp
								RayTracer.cpp
								main.cpp
								GTRenderer.cpp )

add_executable( GTRenderer main.cpp )
target_link_libraries( GTRenderer RayTracer)
