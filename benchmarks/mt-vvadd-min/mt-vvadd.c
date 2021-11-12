// See LICENSE for license details.

//**************************************************************************
// Vector-vector add benchmark
//--------------------------------------------------------------------------
// Author  : Andrew Waterman
// TA      : Christopher Celio
// Student : 
//
// This benchmark adds two vectors and writes the results to a
// third vector. The input data (and reference data) should be
// generated using the vvadd_gendata.pl perl script and dumped
// to a file named dataset.h 

// Update: This benchmark is 

//--------------------------------------------------------------------------
// Includes 

#include <string.h>
#include <stdlib.h>
#include <stdio.h>



  
//--------------------------------------------------------------------------
// Basic Utilities and Multi-thread Support

#include "util.h"



#define DATA_SIZE 8

typedef double data_t;

static data_t input1_data[DATA_SIZE] = 
{
  0.00, 15.00, 10.00, 3.00, 14.00, 6.00, 2.00, 18.00
};

static data_t input2_data[DATA_SIZE] = 
{
  8.00, 6.00, 0.00, 18.00, 6.00, 10.00, 1.00, 2.00
};

static data_t verify_data[DATA_SIZE] = 
{
  8.00, 21.00, 10.00, 21.00, 20.00, 16.00, 3.00, 20.00
};





//--------------------------------------------------------------------------
// vvadd function

void __attribute__((noinline)) vvadd(int coreid, int ncores, size_t n, const data_t* x, const data_t* y, data_t* z)
{
   size_t i;

   // interleave accesses
   for (i = coreid; i < n; i+=ncores)
   {
      z[i] = x[i] + y[i];
   }
}



//--------------------------------------------------------------------------
// Main
//
// all threads start executing thread_entry(). Use their "coreid" to
// differentiate between threads (each thread is running on a separate core).
  
void thread_entry(int cid, int nc)
{
    // static allocates data in the binary, which is visible to both threads
    static data_t results_data[DATA_SIZE];


    if (cid != 0) {
        // All cores except core 0 go to idle
        printf("Core %d go to idle\n", cid);
        while(1);
    }


    // First do out-of-place vvadd

    printf("Do out-of-place vvadd\n");

    vvadd(cid, 1, DATA_SIZE, input1_data, input2_data, results_data);

    printf("Verifying result\n");

    // essent code might die here
    int res = verifyDouble(DATA_SIZE, results_data, verify_data);
    if(res) exit(res);
   
    printf("Result is correct\n");
    exit(0);
}
