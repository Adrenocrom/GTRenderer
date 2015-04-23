cmake_minimum_required( VERSION 2.8 )

project( GTRenderer )

set( CMAKE_BUILD_TYPE "RELEASE" )

#FIND_PACKAGE(Qt4 REQUIRED)

#include( ${QT_USE_FILE} )
#add_definitions( ${QT_DEFINITIONS} )

#find_package(CUDA REQUIRED)


FIND_PACKAGE(CUDA REQUIRED)
if(CUDA_FOUND)
	add_definitions( -DUSECUDA )

	INCLUDE(FindCUDA)
	INCLUDE_DIRECTORIES(/usr/local/cuda-5.5/include common/inc)

	FILE(GLOB SOURCES "*.cu" "*.cpp" "*.c" "*.h")
	CUDA_ADD_EXECUTABLE(CURenderer ${SOURCES})

	LIST(APPEND CMAKE_CXX_FLAGS "-std=c++11 -O3 -ffast-math -Wall")

	LIST(APPEND CUDA_NVCC_FLAGS --compiler-options -fno-strict-aliasing -lineinfo -use_fast_math -Xptxas -dlcm=cg)
	LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_20,code=sm_20)
	LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_30,code=sm_30)
	LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_35,code=sm_35)

	TARGET_LINK_LIBRARIES(CURenderer /usr/local/cuda-5.5/lib64/libcudart.so )

else()
	set (CaMAKE_CXX_FLAGS "-Wall -p -O2 -lcudart -pthread -std=c++11 -Wl,--no-as-needed")
	add_definitions(${CMAKE_CXX_FLAGS})

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
	target_link_libraries( GTRenderer RayTracer ${QT_LIBRARIES} )
	target_link_libraries( GTRenderer RayTracer )

endif()


