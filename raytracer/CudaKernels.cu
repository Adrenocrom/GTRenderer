//#include "CudaKernels.h"

#include <iostream>
#include <vector_types.h>
#include <vector_functions.h>
#include <math_functions.h>
//#include <cutil_math.h>


#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/sequence.h>

#define N 10000

typedef struct {
    double3 p;
	 double r;
} SSphere;

typedef struct {
	double3 o;
	double3 d;
} SRay;

typedef struct {
	double tn;
	double tf;
	double l;
} SInInfo;

__device__ double3 minus(const double3& u, const double3& v) {
	return make_double3(u.x - v.x, u.y - v.y, u.z - v.z);
}

__device__ double dot(const double3& u, const double3& v) {
	return u.x*v.x + u.y*v.y + u.z*v.z;
}


__device__ int RaySphereIntersection(const SRay  &ray, const SSphere &sphere, SInInfo &t)
{
	double b, c, d;

	double3 sr = minus(ray.o, sphere.p);
	b =  dot(sr,ray.d);
	c = dot(sr,sr) - (sphere.r*sphere.r);
	d = b*b - c;
	if (d > 0) 
	{
		double e = sqrt(d);
		t.tn = -b-e;
		t.tf = -b+e;
		return 1;
	}
	return 0;
}


SSphere* dev_spheres;

__global__ void add(int *a, int *b, int *c) {
	int tID = blockIdx.x;

	if (tID < N)
		c[tID] = a[tID] + b[tID];
}

__global__ void hit(SSphere *s, int* r) {
	int tID = blockIdx.x;

	if(tID < 2) {
		if(s[tID].r == 2.0)
			r[tID] = 1;
		else
			r[tID] = 0;
	}
}

void loadUpScene() {
	SSphere spheres[2];
	spheres[0].p = make_double3(0.0, 0.0, 0.0);
	spheres[0].r = 2.0;
	spheres[1].p = make_double3(0.0, 0.0, 0.0);
	spheres[1].r = 2.0;


	int r[2];
	int* dev_r;

	int num = 2;

	cudaMalloc((void **) &dev_spheres, num * sizeof(SSphere));
	cudaMemcpy(dev_spheres, spheres, 2*sizeof(SSphere), cudaMemcpyHostToDevice);

	cudaMalloc((void **) &dev_r, 2 * sizeof(int));

	hit<<<N, 1>>>(dev_spheres, dev_r);

	cudaMemcpy(r, dev_r, 2*sizeof(int), cudaMemcpyDeviceToHost);

	std::cout<<r[0]<<" -- "<<r[1]<<std::endl;
}
void someOperation() {
	int a[N], b[N], c[N];
	int *dev_a, *dev_b, *dev_c;

	cudaMalloc((void **) &dev_a, N*sizeof(int));
	cudaMalloc((void **) &dev_b, N*sizeof(int));
	cudaMalloc((void **) &dev_c, N*sizeof(int));

	// Fill Arrays
	for (int i = 0; i < N; i++) {
		a[i] = i,
		b[i] = 1;
	}

	cudaMemcpy(dev_a, a, N*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, N*sizeof(int), cudaMemcpyHostToDevice);

	add<<<N,1>>>(dev_a, dev_b, dev_c);

	cudaMemcpy(c, dev_c, N*sizeof(int), cudaMemcpyDeviceToHost);
	
	for (int i = 0; i < N; i++)
		std::cout<<a[i]<<"+"<< b[i]<<"="<<c[i]<<std::endl;

	// initialize all ten integers of a device_vector to 1
	thrust::device_vector<int> D(10, 1);
    // set the first seven elements of a vector to 9
   thrust::fill(D.begin(), D.begin() + 7, 9);
		    // initialize a host_vector with the first five elements of D
   thrust::host_vector<int> H(D.begin(), D.begin() + 5);
		      // set the elements of H to 0, 1, 2, 3, ...
	thrust::sequence(H.begin(), H.end());
					     // copy all of H back to the beginning of 
	thrust::copy(H.begin(), H.end(), D.begin());
								    // print D
	for(int i = 0; i < D.size(); i++)
		std::cout << "D[" << i << "] = " << D[i] << std::endl;
}

/*
int main() {
	int a[N], b[N], c[N];
	int *dev_a, *dev_b, *dev_c;

	cudaMalloc((void **) &dev_a, N*sizeof(int));
	cudaMalloc((void **) &dev_b, N*sizeof(int));
	cudaMalloc((void **) &dev_c, N*sizeof(int));

	// Fill Arrays
	for (int i = 0; i < N; i++) {
		a[i] = i,
		b[i] = 1;
	}

	cudaMemcpy(dev_a, a, N*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, N*sizeof(int), cudaMemcpyHostToDevice);

	add<<<N,1>>>(dev_a, dev_b, dev_c);

	cudaMemcpy(c, dev_c, N*sizeof(int), cudaMemcpyDeviceToHost);

	return 0;
}*/

