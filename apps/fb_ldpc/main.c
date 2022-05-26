#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "printf.h"

#define q_field 16
#define m_field 4
#define N_code 32
#define M_code 16
#define dc 4
#define dv 2

int64_t R[q_field][dc] = {
    {6,11,6,12},
    {2,2,5,5},
    {1,4,10,4},
    {9,8,3,0},
    {4,1,3,4},
    {10,5,9,3},
    {4,5,8,8},
    {1,0,1,8},
    {0,3,7,13},
    {0,0,2,7},
    {9,4,8,4},
    {8,6,7,9},
    {6,7,5,8},
    {3,6,4,0},
    {11,9,0,9},
    {8,10,2,3}
};

int64_t result[q_field][dc] = {
    {1,1,1,1},
    {1,1,0,1},
    {2,0,1,1},
    {1,1,0,0},
    {2,1,0,1},
    {2,1,0,0},
    {1,1,0,1},
    {0,0,1,1},
    {1,1,1,1},
    {0,1,1,1},
    {1,1,0,0},
    {0,0,1,1},
    {0,1,1,1},
    {1,1,0,1},
    {1,1,0,0},
    {2,0,1,1}
};

int wires[q_field][q_field] = {
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
    {1,0,5,9,15,2,11,14,10,3,8,6,13,12,7,4},
    {2,5,0,6,10,1,3,12,15,11,4,9,7,14,13,8},
    {3,9,6,0,7,11,2,4,13,1,12,5,10,8,15,14},
    {4,15,10,7,0,8,12,3,5,14,2,13,6,11,9,1},
    {5,2,1,11,8,0,9,13,4,6,15,3,14,7,12,10},
    {6,11,3,2,12,9,0,10,14,5,7,1,4,15,8,13},
    {7,14,12,4,3,13,10,0,11,15,6,8,2,5,1,9},
    {8,10,15,13,5,4,14,11,0,12,1,7,9,3,6,2},
    {9,3,11,1,14,6,5,15,12,0,13,2,8,10,4,7},
    {10,8,4,12,2,15,7,6,1,13,0,14,3,9,11,5},
    {11,6,9,5,13,3,1,8,7,2,14,0,15,4,10,12},
    {12,13,7,10,6,14,4,2,9,8,3,15,0,1,5,11},
    {13,12,14,8,11,7,15,5,3,10,9,4,1,0,2,6},
    {14,7,13,15,9,12,8,1,6,4,11,10,5,2,0,3},
    {15,4,8,14,1,10,13,9,2,7,5,12,11,6,3,0}
};

#define VECTOR_EXT

int main(void) 
{
    printf("--------------------------\n");
    printf("Forward Backward algorithm\n");
    printf("--------------------------\n");
    
    int i, j, k, a;
    int64_t R_Forward[q_field][dc], R_Backward[q_field][dc], R_Aux[q_field][dc];
    int64_t R_compare, R_compare_2, R_compare_3, R_compare_aux;
    int64_t min_temp, min_temp_2;
    int wires_aux;
    unsigned long int block_size_p;

    // Vector configuration
    asm volatile("vsetvli %0, %1, e64, m1, ta, ma" : "=r"(block_size_p) : "r"(q_field));

    // Clean Forward and Backward variables and set value to first and last column
    // Clean R_Aux
#ifndef VECTOR_EXT    
    for(i=0;i<q_field;i++){        
        R_Forward[i][0] = R[i][0];
        R_Backward[i][dc-1] = R[i][dc-1];
        R_Aux[i][dc-1] = R[i][dc-1];
    }    
#else
    asm volatile("addi	t0, zero, %0;" :: "I"(32));  // 64 (int64_t) * 4 (columns) / 8

    asm volatile("vlse64.v v2, (%0), t0;" ::"r"(R)); 
    asm volatile("vsse64.v v2, (%0), t0;" ::"r"(R_Forward));

    asm volatile("vlse64.v v2, (%0), t0;" ::"r"(&R[0][dc-1])); 
    asm volatile("vsse64.v v2, (%0), t0;" ::"r"(&R_Backward[0][dc-1]));
    asm volatile("vsse64.v v2, (%0), t0;" ::"r"(&R_Aux[0][dc-1]));
#endif    
    asm volatile("vmv.v.i v0, 1;");
    asm volatile("vloxei64.v v2, (%0), v0;" ::"r"(R)); 
    asm volatile("vsse64.v v2, (%0), t0;" ::"r"(R_Forward));
    for(i=0;i<q_field;i++)
        printf("%d\n", R_Forward[i][0]);

    for(a=2;a<dc;a++){
        for(i=0;i<q_field;i++){
            min_temp = 10000;
            min_temp_2 = 10000;
            // Search maximum
            for(k=0;k<q_field;k++){
                wires_aux = wires[k][i];
                // Forward
                if(R_Forward[k][a-2] > R[wires_aux][a-1])
                    R_compare = R_Forward[k][a-2];
                else
                    R_compare = R[wires_aux][a-1];

                // Backward
                if(R_Backward[k][5-a] > R[wires_aux][4-a])
                    R_compare_2 = R_Backward[k][5-a];
                else
                    R_compare_2 = R[wires_aux][4-a];

                // Search minimum
                // Forward
                if(R_compare < min_temp)
                    min_temp = R_compare;
                // Backward
                if(R_compare_2 < min_temp_2)
                    min_temp_2 = R_compare_2;
            }
            //printf("%d \n", R_compare);
            R_Forward[i][a-1] = min_temp;
            R_Backward[i][4-a] = min_temp_2;
        }
        
        // Standard Min Max
        for(i=0;i<q_field;i++){
            min_temp = 10000;
            // Search maximum
            for(k=0;k<q_field;k++){
                wires_aux = wires[k][i];
                if(R_Forward[k][a-2] > R_Backward[wires_aux][a])
                        R_compare_3 = R_Forward[k][a-2];
                    else
                        R_compare_3 = R_Backward[wires_aux][a];
                // Search minimum
                if(R_compare_3 < min_temp)
                    min_temp = R_compare_3;
            }        

            R_Aux[i][a-1] = min_temp;
        } 
    }
/*
    for(i=0;i<q_field;i++){
        R_Aux[i][0] =       R_Backward[i][1];
        R_Aux[i][dc-1] =    R_Forward[i][dc-2];
    }
    


    // Print
    int error = 0;
    for(i=0;i<q_field;i++){
        for(j=0;j<dc;j++)
            if(result[i][j] != R_Aux[i][j])
                error = 1;
            //printf("%d ",R_Aux[i][j]);
        //printf("\n");
    }

    if(error ==1)
        printf("ERROR\n");
    else 
        printf("SUCCESS\n");*/

}