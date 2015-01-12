cmake_minimum_required( VERSION 2.6 )

project( GTRenderer )

set( CMAKE_BUILD_TYPE "RELEASE" )

add_definitions( "-std=c++11" )

include_directories( include . )

add_library( RayTracer	Vector3.cpp
								Sphere.cpp
								Ray.cpp
								LightSource.cpp
								main.cpp
								GTRenderer.cpp )

add_executable( GTRenderer main.cpp )
target_link_libraries( GTRenderer RayTracer)
