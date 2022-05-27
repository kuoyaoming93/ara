#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "printf.h"
#include "runtime.h"

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

int64_t wires[q_field][q_field] = {
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

// Index = wires * 8 bytes * 4 columns (dc)
int64_t wires_idx[q_field][q_field] = {
    {0,32,64,96,128,160,192,224,256,288,320,352,384,416,448,480},
    {32,0,160,288,480,64,352,448,320,96,256,192,416,384,224,128},
    {64,160,0,192,320,32,96,384,480,352,128,288,224,448,416,256},
    {96,288,192,0,224,352,64,128,416,32,384,160,320,256,480,448},
    {128,480,320,224,0,256,384,96,160,448,64,416,192,352,288,32},
    {160,64,32,352,256,0,288,416,128,192,480,96,448,224,384,320},
    {192,352,96,64,384,288,0,320,448,160,224,32,128,480,256,416},
    {224,448,384,128,96,416,320,0,352,480,192,256,64,160,32,288},
    {256,320,480,416,160,128,448,352,0,384,32,224,288,96,192,64},
    {288,96,352,32,448,192,160,480,384,0,416,64,256,320,128,224},
    {320,256,128,384,64,480,224,192,32,416,0,448,96,288,352,160},
    {352,192,288,160,416,96,32,256,224,64,448,0,480,128,320,384},
    {384,416,224,320,192,448,128,64,288,256,96,480,0,32,160,352},
    {416,384,448,256,352,224,480,160,96,320,288,128,32,0,64,192},
    {448,224,416,480,288,384,256,32,192,128,352,320,160,64,0,96},
    {480,128,256,448,32,320,416,288,64,224,160,384,352,192,96,0}
};

int64_t min_vec[32] = {1,1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,0,0,0,1,1,1,0,1,1,0,0,1};

#define VECTOR_EXT

int main(void) 
{
    printf("--------------------------\n");
    printf("Forward Backward algorithm\n");
    printf("--------------------------\n");
    
    int i, j, k, a;
    int64_t R_Forward[q_field][dc], R_Backward[q_field][dc], R_Aux[q_field][dc];
    int64_t R_compare, R_compare_2, R_compare_3, R_compare_aux;
    int64_t R_compare_vec[q_field], R_compare_vec2[q_field], R_compare_vec3[q_field];
    int64_t min_temp, min_temp_2, min_temp_3, min3;
    int wires_aux;
    int aux_aux[q_field];
    unsigned long int block_size_p;

    // Vector configuration
    asm volatile("vsetvli %0, %1, e64, m1, ta, ma" : "=r"(block_size_p) : "r"(q_field));

    // Metrics    
    start_timer();	
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

    asm volatile("vlse64.v v2, (%0), t0;" ::"r"(&R[0][0])); 
    asm volatile("vsse64.v v2, (%0), t0;" ::"r"(&R_Forward[0][0]));

    asm volatile("vlse64.v v2, (%0), t0;" ::"r"(&R[0][dc-1])); 
    asm volatile("vsse64.v v2, (%0), t0;" ::"r"(&R_Backward[0][dc-1]));
    asm volatile("vsse64.v v2, (%0), t0;" ::"r"(&R_Aux[0][dc-1]));
#endif    

    for(a=2;a<dc;a++){
        for(i=0;i<q_field;i++){
            min_temp = 10000;
            min_temp_2 = 10000;

#ifndef VECTOR_EXT
            // Load wire index in v0
            asm volatile("addi	t0, zero, %0;" :: "I"(128)); // 64 (int64_t) * 16 (columns) / 8
            asm volatile("vlse64.v v0, (%0), t0;" ::"r"(&wires_idx[0][i])); 
            asm volatile("addi	t0, zero, %0;" :: "I"(32));  // 64 (int64_t) * 4 (columns) / 8

            /********************************
             ********** Forward *************
             *******************************/       
            // Load R[wires_aux][a-1]
            asm volatile("vluxei64.v v2, (%0), v0;" ::"r"(&R[0][a-1])); 
            // Load R_Forward[k][a-2]
            asm volatile("vlse64.v v4, (%0), t0;" ::"r"(&R_Forward[0][a-2]));
            // Max find
            asm volatile("vmax.vv v6, v2, v4;");
            // Store 
            asm volatile("vse64.v v6, (%0);" ::"r"(R_compare_vec));
            
            /********************************
             ********** Backward ************
             *******************************/
            // Load R[wires_aux][4-a]
            asm volatile("vluxei64.v v2, (%0), v0;" ::"r"(&R[0][4-a])); 
            // Load R_Forward[k][5-a]
            asm volatile("vlse64.v v4, (%0), t0;" ::"r"(&R_Backward[0][5-a]));
            // Max find
            asm volatile("vmax.vv v6, v2, v4;");
            // Store 
            asm volatile("vse64.v v6, (%0);" ::"r"(R_compare_vec2));

            // Search minimum
            for(k=0;k<q_field;k++){
                if(R_compare_vec[k] < min_temp)
                    min_temp = R_compare_vec[k];
                if(R_compare_vec2[k] < min_temp_2)
                    min_temp_2 = R_compare_vec2[k];
            }
#else           
            for(k=0;k<q_field;k++){
                // Search maximum
                wires_aux = wires[k][i];                
                // Forward
                if(R_Forward[k][a-2] > R[wires_aux][a-1])
                    R_compare = R_Forward[k][a-2];                            
                else
                    R_compare = R[wires_aux][a-1];
                aux_aux[k] = R_compare;

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
#endif
            R_Forward[i][a-1] = min_temp;
            R_Backward[i][4-a] = min_temp_2;
        }
        
        
            
#ifdef VECTOR_EXT
            #pragma GCC push_options
            #pragma GCC optimize("O0")
            // Load wire index in v0
            asm volatile("vmv.v.i v25, 15;"); 
            asm volatile("addi	t0, zero, %0;" :: "I"(128)); // 64 (int64_t) * 16 (columns) / 8
            asm volatile("vlse64.v v0, (%0), t0;" ::"r"(&wires_idx[0][0]));          
            asm volatile("vlse64.v v1, (%0), t0;" ::"r"(&wires_idx[0][1]));
            asm volatile("vlse64.v v2, (%0), t0;" ::"r"(&wires_idx[0][2]));
            asm volatile("vlse64.v v3, (%0), t0;" ::"r"(&wires_idx[0][3]));
            asm volatile("vlse64.v v4, (%0), t0;" ::"r"(&wires_idx[0][4]));
            asm volatile("vlse64.v v5, (%0), t0;" ::"r"(&wires_idx[0][5]));
            asm volatile("vlse64.v v6, (%0), t0;" ::"r"(&wires_idx[0][6]));
            asm volatile("vlse64.v v7, (%0), t0;" ::"r"(&wires_idx[0][7]));   

            // Load R_Backward[wires_aux][a]
            asm volatile("vluxei64.v v8, (%0), v0;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v9, (%0), v1;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v10, (%0), v2;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v11, (%0), v3;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v12, (%0), v4;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v13, (%0), v5;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v14, (%0), v6;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v15, (%0), v7;" ::"r"(&R_Backward[0][a])); 

            // Load R_Forward[k][a-2]
            asm volatile("addi	t0, zero, %0;" :: "I"(32));  // 64 (int64_t) * 4 (columns) / 8
            asm volatile("vlse64.v v16, (%0), t0;" ::"r"(&R_Forward[0][a-2]));

            // Max find
            asm volatile("vmax.vv v17, v16, v8;");
            asm volatile("vmax.vv v18, v16, v9;");
            asm volatile("vmax.vv v19, v16, v10;");
            asm volatile("vmax.vv v20, v16, v11;");
            asm volatile("vmax.vv v21, v16, v12;");
            asm volatile("vmax.vv v22, v16, v13;");
            asm volatile("vmax.vv v23, v16, v14;");
            asm volatile("vmax.vv v24, v16, v15;");

            // Min find
            printf("HOLA\n");
            asm volatile("vredmin.vs v0, v17, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v1, v18, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v2, v19, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v3, v20, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v4, v21, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v5, v22, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v6, v23, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v7, v24, v25;"); 
            printf("HOLA\n");

            // Store 
            asm volatile("vse64.v v0, (%0);" ::"r"(&R_compare_vec3[0]));
            asm volatile("vse64.v v1, (%0);" ::"r"(&R_compare_vec3[1]));
            asm volatile("vse64.v v2, (%0);" ::"r"(&R_compare_vec3[2]));
            asm volatile("vse64.v v3, (%0);" ::"r"(&R_compare_vec3[3]));
            asm volatile("vse64.v v4, (%0);" ::"r"(&R_compare_vec3[4]));
            asm volatile("vse64.v v5, (%0);" ::"r"(&R_compare_vec3[5]));
            asm volatile("vse64.v v6, (%0);" ::"r"(&R_compare_vec3[6]));
            asm volatile("vse64.v v7, (%0);" ::"r"(&R_compare_vec3[7]));

            // Load wire index in v0
            asm volatile("vmv.v.i v25, 15;"); 
            asm volatile("addi	t0, zero, %0;" :: "I"(128)); // 64 (int64_t) * 16 (columns) / 8
            asm volatile("vlse64.v v0, (%0), t0;" ::"r"(&wires_idx[0][8]));          
            asm volatile("vlse64.v v1, (%0), t0;" ::"r"(&wires_idx[0][9]));
            asm volatile("vlse64.v v2, (%0), t0;" ::"r"(&wires_idx[0][10]));
            asm volatile("vlse64.v v3, (%0), t0;" ::"r"(&wires_idx[0][11]));
            asm volatile("vlse64.v v4, (%0), t0;" ::"r"(&wires_idx[0][12]));
            asm volatile("vlse64.v v5, (%0), t0;" ::"r"(&wires_idx[0][13]));
            asm volatile("vlse64.v v6, (%0), t0;" ::"r"(&wires_idx[0][14]));
            asm volatile("vlse64.v v7, (%0), t0;" ::"r"(&wires_idx[0][15]));   

            // Load R_Backward[wires_aux][a]
            asm volatile("vluxei64.v v8, (%0), v0;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v9, (%0), v1;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v10, (%0), v2;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v11, (%0), v3;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v12, (%0), v4;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v13, (%0), v5;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v14, (%0), v6;" ::"r"(&R_Backward[0][a])); 
            asm volatile("vluxei64.v v15, (%0), v7;" ::"r"(&R_Backward[0][a])); 

            // Load R_Forward[k][a-2]
            asm volatile("addi	t0, zero, %0;" :: "I"(32));  // 64 (int64_t) * 4 (columns) / 8
            asm volatile("vlse64.v v16, (%0), t0;" ::"r"(&R_Forward[0][a-2]));

            // Max find
            asm volatile("vmax.vv v17, v16, v8;");
            asm volatile("vmax.vv v18, v16, v9;");
            asm volatile("vmax.vv v19, v16, v10;");
            asm volatile("vmax.vv v20, v16, v11;");
            asm volatile("vmax.vv v21, v16, v12;");
            asm volatile("vmax.vv v22, v16, v13;");
            asm volatile("vmax.vv v23, v16, v14;");
            asm volatile("vmax.vv v24, v16, v15;");

            // Min find
            printf("HOLA\n");
            asm volatile("vredmin.vs v0, v17, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v1, v18, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v2, v19, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v3, v20, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v4, v21, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v5, v22, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v6, v23, v25;"); 
            printf("HOLA\n");
            asm volatile("vredmin.vs v7, v24, v25;"); 

            // Store 
            asm volatile("vse64.v v0, (%0);" ::"r"(&R_compare_vec3[8]));
            asm volatile("vse64.v v1, (%0);" ::"r"(&R_compare_vec3[9]));
            asm volatile("vse64.v v2, (%0);" ::"r"(&R_compare_vec3[10]));
            asm volatile("vse64.v v3, (%0);" ::"r"(&R_compare_vec3[11]));
            asm volatile("vse64.v v4, (%0);" ::"r"(&R_compare_vec3[12]));
            asm volatile("vse64.v v5, (%0);" ::"r"(&R_compare_vec3[13]));
            asm volatile("vse64.v v6, (%0);" ::"r"(&R_compare_vec3[14]));
            asm volatile("vse64.v v7, (%0);" ::"r"(&R_compare_vec3[15]));

            for(k=0;k<q_field;k++){
                R_Aux[k][a-1] = R_compare_vec3[k];
                printf("%d\t%d\n",min_vec[((a-2)*16+k)],R_compare_vec3[k]);
            }

            #pragma GCC pop_options
            /*#pragma GCC push_options
            #pragma GCC optimize("O0")
            for(i=0;i<q_field;i++){
            min3 = 10000;
            // Load wire index in v0
            asm volatile("vmv.v.i v10, 15;"); 
            asm volatile("addi	t0, zero, %0;" :: "I"(128)); // 64 (int64_t) * 16 (columns) / 8
            asm volatile("vlse64.v v0, (%0), t0;" ::"r"(&wires_idx[0][i]));             

            // Load R_Backward[wires_aux][a]
            asm volatile("vluxei64.v v2, (%0), v0;" ::"r"(&R_Backward[0][a])); 
            // Load R_Forward[k][a-2]
            asm volatile("addi	t0, zero, %0;" :: "I"(32));  // 64 (int64_t) * 4 (columns) / 8
            asm volatile("vlse64.v v4, (%0), t0;" ::"r"(&R_Forward[0][a-2]));
            // Max find
            asm volatile("vmax.vv v6, v2, v4;");
            // Store 
            //asm volatile("vse64.v v6, (%0);" ::"r"(R_compare_vec3));
            
            // Search minimum
            //printf("Hola\n");
            asm volatile("vredmin.vs v8, v6, v10;"); 
            asm volatile("vse64.v v8, (%0);" ::"r"(R_compare_vec3));
            /*for(k=0;k<q_field;k++){
                if(R_compare_vec3[k] < min3){
                    min3 = R_compare_vec3[k];
                }
            }
            R_Aux[i][a-1] = R_compare_vec3[0];*/
            
            //printf("%d\t%d\t%d\n",((a-2)*16+i),min_vec[((a-2)*16+i)],min3);*/
#else
        // Standard Min Max
        for(i=0;i<q_field;i++){
            min_temp_3 = 10000;        
            // Search maximum
            for(k=0;k<q_field;k++){
                wires_aux = wires[k][i];
                if(R_Forward[k][a-2] > R_Backward[wires_aux][a])
                        R_compare_3 = R_Forward[k][a-2];
                    else
                        R_compare_3 = R_Backward[wires_aux][a];
                // Search minimum
                if(R_compare_3 < min_temp_3)
                    min_temp_3 = R_compare_3;                
            }        
            R_Aux[i][a-1] = min_temp_3;        
        }    
#endif            
    }

#ifndef VECTOR_EXT
    for(i=0;i<q_field;i++){
        R_Aux[i][0] =       R_Backward[i][1];
        R_Aux[i][dc-1] =    R_Forward[i][dc-2];
    }
#else
    asm volatile("addi	t0, zero, %0;" :: "I"(32));  // 64 (int64_t) * 4 (columns) / 8

    asm volatile("vlse64.v v2, (%0), t0;" ::"r"(&R_Backward[0][1])); 
    asm volatile("vsse64.v v2, (%0), t0;" ::"r"(&R_Aux[0][0]));

    asm volatile("vlse64.v v2, (%0), t0;" ::"r"(&R_Forward[0][dc-2])); 
    asm volatile("vsse64.v v2, (%0), t0;" ::"r"(&R_Aux[0][dc-1]));
#endif

    stop_timer();
    int64_t runtime = get_timer();

    printf("The execution took %d cycles.\n", runtime);
    


    // Print
    int error = 0;
    for(i=0;i<q_field;i++){
        for(j=0;j<dc;j++){
            if(result[i][j] != R_Aux[i][j])
                error = 1;
            //printf("%d\t%d\n",result[i][j], R_Aux[i][j]);
        }
        //printf("\n");
    }

    if(error ==1)
        printf("ERROR\n");
    else 
        printf("SUCCESS\n");

}