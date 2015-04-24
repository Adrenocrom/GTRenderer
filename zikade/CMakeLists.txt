cmake_minimum_required( VERSION 2.8 )

project( zikade )

set( CMAKE_BUILD_TYPE "RELEASE" )
set( CMAKE_CXX_FLAGS "-Wall -p -O2 -pthread -std=c++11 -Wl,--no-as-needed" )
add_definitions( ${CMAKE_CXX_FLAGS} )

find_package( OpenMP )
if( OPENMP_FOUND) 
	set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}" )
	set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )
endif()

include_directories( include . )
add_library( zikade 	light.cpp
							lightTracer.cpp
							si.cpp
							zikade.cpp
							main.cpp )

add_executable( Zikade main.cpp )
target_link_libraries( Zikade zikade )
