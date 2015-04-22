cmake_minimum_required( VERSION 2.8 )

project( GTRenderer )

include("findcudalib.mk")

set( CMAKE_BUILD_TYPE "RELEASE" )

#FIND_PACKAGE(Qt4 REQUIRED)

#include( ${QT_USE_FILE} )
#add_definitions( ${QT_DEFINITIONS} )

find_package ( Threads REQUIRED )
find_package (CUDA QUIET REQUIRED)

set (CMAKE_CXX_FLAGS "-Wall -pthread -std=c++11 -Wl,--no-as-needed")
add_definitions(${CMAKE_CXX_FLAGS})

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
target_link_libraries( GTRenderer RayTracer ${CMAKE_THREAD_LIBS_INIT})


#add_library( cudaTracer CudaKernels.cu )
#list(APPEND CUDA_NVCC_FLAGS "-O2;-DVERBOSE")
#SET(CUDA_PROPAGATE_HOST_FLAGS OFF)

#cuda_compile(CUDAKernels_O CudaMain.cpp CudaKernels.cu)
#cuda_add_executable(CudaRenderer CudaMain.cpp)
#add_executable( CudaRenderer CudaKernels.cu)

#add_executable( GTRenderer main.cpp )
#target_link_libraries( GTRenderer RayTracer ${QT_LIBRARIES} )
#target_link_libraries(CudaRenderer cudaTracer)

#target_link_libraries( GTRenderer RayTracer ${CMAKE_THREAD_LIBS_INIT})
