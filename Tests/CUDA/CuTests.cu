/**
 * @File cuTests.cu
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/7/3
 * @Brief This file is part of SLib.
 */

#include "CuTests.hpp"
#include "SLibCUDA/Math.hpp"

#define T(expr) ((expr) ? 0 : 1)

__global__ void TestAbs(int* numErrors)
{
    // numErrors += T(slib::Abs(-42) == 42);
}

int TestCommon()
{
    int* dev_pNumErrors = nullptr;

    cudaMalloc(&dev_pNumErrors, sizeof(int));
    
    TestAbs<<<1, 1>>>(dev_pNumErrors);

    int numErrors;

    cudaMemcpy(&numErrors, dev_pNumErrors, sizeof(int), cudaMemcpyDeviceToHost);

    return numErrors;
}