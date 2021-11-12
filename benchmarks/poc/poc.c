
//**************************************************************************
// Proof-of Concept
//--------------------------------------------------------------------------
//
// This is an empty benchmark
 
#include "util.h"


#define DATA_SIZE 8 

typedef double data_t;

data_t input11_data[DATA_SIZE] = 
{
    1.00, 15.00, 10.00, 3.00, 14.00, 6.00, 2.00, 18.00
};

data_t input22_data[DATA_SIZE] = 
{
    8.00, 6.00, 0.00, 18.00, 6.00, 10.00, 1.00, 2.00
};

data_t verifyy_data[DATA_SIZE] = 
{
    9.00, 21.00, 10.00, 21.00, 20.00, 16.00, 3.00, 20.00
};

void thread_entry(int cid, int nc) {
    // Only do single core, avoid interference
    if (cid != 0){
        printf("Core %d go to sleep\n");
        while (1);
    }


    for (int i = 0; i < DATA_SIZE; i++) {
        double a = input11_data[i];
        double b = input22_data[i];
        double r = verifyy_data[i];

        
        printf("Core %d: i[%d] copy data: a[%llx] b[%llx] r[%llx] real[%llx]\n", cid, i, a, b, r, a+b);
        printf("Core %d: i[%d] read data: a[%llx] b[%llx] r[%llx] real[%llx]\n", cid, i, input11_data[i], input22_data[i], verifyy_data[i], input11_data[i]+input22_data[i]);

    }

    exit(0);


}


// int main( int argc, char* argv[] )
// {


//     // 
//     return 0;
// }
