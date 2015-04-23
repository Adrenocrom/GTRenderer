//#include "CudaKernels.h"

#include <iostream>
#include <vector_types.h>

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/sequence.h>

#define N 10000

__global__ void add(int *a, int *b, int *c) {
	int tID = blockIdx.x;

	if (tID < N)
		c[tID] = a[tID] + b[tID];
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

