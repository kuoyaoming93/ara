#include <stdint.h>
#include <string.h>

#include "printf.h"
#include "runtime.h"

#define q_field 16

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

int64_t golden[q_field][q_field] = {
    {0,33,66,99,132,165,198,231,264,297,330,363,396,429,462,495},
    {33,0,165,297,495,66,363,462,330,99,264,198,429,396,231,132},
    {66,165,0,198,330,33,99,396,495,363,132,297,231,462,429,264},
    {99,297,198,0,231,363,66,132,429,33,396,165,330,264,495,462},
    {132,495,330,231,0,264,396,99,165,462,66,429,198,363,297,33},
    {165,66,33,363,264,0,297,429,132,198,495,99,462,231,396,330},
    {198,363,99,66,396,297,0,330,462,165,231,33,132,495,264,429},
    {231,462,396,132,99,429,330,0,363,495,198,264,66,165,33,297},
    {264,330,495,429,165,132,462,363,0,396,33,231,297,99,198,66},
    {297,99,363,33,462,198,165,495,396,0,429,66,264,330,132,231},
    {330,264,132,396,66,495,231,198,33,429,0,462,99,297,363,165},
    {363,198,297,165,429,99,33,264,231,66,462,0,495,132,330,396},
    {396,429,231,330,198,462,132,66,297,264,99,495,0,33,165,363},
    {429,396,462,264,363,231,495,165,99,330,297,132,33,0,66,198},
    {462,231,429,495,297,396,264,33,198,132,363,330,165,66,0,99},
    {495,132,264,462,33,330,429,297,66,231,165,396,363,198,99,0}
};

int main(void) {
    printf("\n");
    printf("=============\n");
    printf("=  RISC-V V =\n");
    printf("=============\n");
    printf("\n");
    printf("\n");

    int64_t cycles = 0;
    int64_t result[q_field][q_field];

    int64_t opa_0, opb_0, res_0;
    int64_t opa_1, opb_1, res_1;
    int64_t opa_2, opb_2, res_2;
    int64_t opa_3, opb_3, res_3;
    int64_t opa_4, opb_4, res_4;
    int64_t opa_5, opb_5, res_5;
    int64_t opa_6, opb_6, res_6;
    int64_t opa_7, opb_7, res_7;
    int64_t opa_8, opb_8, res_8;
    int64_t opa_9, opb_9, res_9;
    int64_t opa_10, opb_10, res_10;
    int64_t opa_11, opb_11, res_11;
    int64_t opa_12, opb_12, res_12;
    int64_t opa_13, opb_13, res_13;
    int64_t opa_14, opb_14, res_14;
    int64_t opa_15, opb_15, res_15;
    
    int i, j;
    int error = 0;

    unsigned long int block_size_p;
    // Set the vector configuration
    asm volatile("vsetvli %0, %1, e64, m1, ta, ma" : "=r"(block_size_p) : "r"(q_field));
    printf("Block size: %d\n", block_size_p);

    start_timer();

    /*opa_0 = wires[0][0];
    opa_1 = wires[0][1];
    opa_2 = wires[0][2];
    opa_3 = wires[0][3];
    opa_4 = wires[0][4];
    opa_5 = wires[0][5];
    opa_6 = wires[0][6];
    opa_7 = wires[0][7];
    opa_8 = wires[0][8];
    opa_9 = wires[0][9];
    opa_10 = wires[0][10];
    opa_11 = wires[0][11];
    opa_12 = wires[0][12];
    opa_13 = wires[0][13];
    opa_14 = wires[0][14];
    opa_15 = wires[0][15];

    opb_0 = wires_idx[0][0];
    opb_1 = wires_idx[0][1];
    opb_2 = wires_idx[0][2];
    opb_3 = wires_idx[0][3];
    opb_4 = wires_idx[0][4];
    opb_5 = wires_idx[0][5];
    opb_6 = wires_idx[0][6];
    opb_7 = wires_idx[0][7];
    opb_8 = wires_idx[0][8];
    opb_9 = wires_idx[0][9];
    opb_10 = wires_idx[0][10];
    opb_11 = wires_idx[0][11];
    opb_12 = wires_idx[0][12];
    opb_13 = wires_idx[0][13];
    opb_14 = wires_idx[0][14];
    opb_15 = wires_idx[0][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[0][0] = res_0;
    result[0][1] = res_1;
    result[0][2] = res_2;
    result[0][3] = res_3;
    result[0][4] = res_4;
    result[0][5] = res_5;
    result[0][6] = res_6;
    result[0][7] = res_7;
    result[0][8] = res_8;
    result[0][9] = res_9;
    result[0][10] = res_10;
    result[0][11] = res_11;
    result[0][12] = res_12;
    result[0][13] = res_13;
    result[0][14] = res_14;
    result[0][15] = res_15;


    opa_0 = wires[1][0];
    opa_1 = wires[1][1];
    opa_2 = wires[1][2];
    opa_3 = wires[1][3];
    opa_4 = wires[1][4];
    opa_5 = wires[1][5];
    opa_6 = wires[1][6];
    opa_7 = wires[1][7];
    opa_8 = wires[1][8];
    opa_9 = wires[1][9];
    opa_10 = wires[1][10];
    opa_11 = wires[1][11];
    opa_12 = wires[1][12];
    opa_13 = wires[1][13];
    opa_14 = wires[1][14];
    opa_15 = wires[1][15];

    opb_0 = wires_idx[1][0];
    opb_1 = wires_idx[1][1];
    opb_2 = wires_idx[1][2];
    opb_3 = wires_idx[1][3];
    opb_4 = wires_idx[1][4];
    opb_5 = wires_idx[1][5];
    opb_6 = wires_idx[1][6];
    opb_7 = wires_idx[1][7];
    opb_8 = wires_idx[1][8];
    opb_9 = wires_idx[1][9];
    opb_10 = wires_idx[1][10];
    opb_11 = wires_idx[1][11];
    opb_12 = wires_idx[1][12];
    opb_13 = wires_idx[1][13];
    opb_14 = wires_idx[1][14];
    opb_15 = wires_idx[1][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[1][0] = res_0;
    result[1][1] = res_1;
    result[1][2] = res_2;
    result[1][3] = res_3;
    result[1][4] = res_4;
    result[1][5] = res_5;
    result[1][6] = res_6;
    result[1][7] = res_7;
    result[1][8] = res_8;
    result[1][9] = res_9;
    result[1][10] = res_10;
    result[1][11] = res_11;
    result[1][12] = res_12;
    result[1][13] = res_13;
    result[1][14] = res_14;
    result[1][15] = res_15;


    opa_0 = wires[2][0];
    opa_1 = wires[2][1];
    opa_2 = wires[2][2];
    opa_3 = wires[2][3];
    opa_4 = wires[2][4];
    opa_5 = wires[2][5];
    opa_6 = wires[2][6];
    opa_7 = wires[2][7];
    opa_8 = wires[2][8];
    opa_9 = wires[2][9];
    opa_10 = wires[2][10];
    opa_11 = wires[2][11];
    opa_12 = wires[2][12];
    opa_13 = wires[2][13];
    opa_14 = wires[2][14];
    opa_15 = wires[2][15];

    opb_0 = wires_idx[2][0];
    opb_1 = wires_idx[2][1];
    opb_2 = wires_idx[2][2];
    opb_3 = wires_idx[2][3];
    opb_4 = wires_idx[2][4];
    opb_5 = wires_idx[2][5];
    opb_6 = wires_idx[2][6];
    opb_7 = wires_idx[2][7];
    opb_8 = wires_idx[2][8];
    opb_9 = wires_idx[2][9];
    opb_10 = wires_idx[2][10];
    opb_11 = wires_idx[2][11];
    opb_12 = wires_idx[2][12];
    opb_13 = wires_idx[2][13];
    opb_14 = wires_idx[2][14];
    opb_15 = wires_idx[2][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[2][0] = res_0;
    result[2][1] = res_1;
    result[2][2] = res_2;
    result[2][3] = res_3;
    result[2][4] = res_4;
    result[2][5] = res_5;
    result[2][6] = res_6;
    result[2][7] = res_7;
    result[2][8] = res_8;
    result[2][9] = res_9;
    result[2][10] = res_10;
    result[2][11] = res_11;
    result[2][12] = res_12;
    result[2][13] = res_13;
    result[2][14] = res_14;
    result[2][15] = res_15;


    opa_0 = wires[3][0];
    opa_1 = wires[3][1];
    opa_2 = wires[3][2];
    opa_3 = wires[3][3];
    opa_4 = wires[3][4];
    opa_5 = wires[3][5];
    opa_6 = wires[3][6];
    opa_7 = wires[3][7];
    opa_8 = wires[3][8];
    opa_9 = wires[3][9];
    opa_10 = wires[3][10];
    opa_11 = wires[3][11];
    opa_12 = wires[3][12];
    opa_13 = wires[3][13];
    opa_14 = wires[3][14];
    opa_15 = wires[3][15];

    opb_0 = wires_idx[3][0];
    opb_1 = wires_idx[3][1];
    opb_2 = wires_idx[3][2];
    opb_3 = wires_idx[3][3];
    opb_4 = wires_idx[3][4];
    opb_5 = wires_idx[3][5];
    opb_6 = wires_idx[3][6];
    opb_7 = wires_idx[3][7];
    opb_8 = wires_idx[3][8];
    opb_9 = wires_idx[3][9];
    opb_10 = wires_idx[3][10];
    opb_11 = wires_idx[3][11];
    opb_12 = wires_idx[3][12];
    opb_13 = wires_idx[3][13];
    opb_14 = wires_idx[3][14];
    opb_15 = wires_idx[3][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[3][0] = res_0;
    result[3][1] = res_1;
    result[3][2] = res_2;
    result[3][3] = res_3;
    result[3][4] = res_4;
    result[3][5] = res_5;
    result[3][6] = res_6;
    result[3][7] = res_7;
    result[3][8] = res_8;
    result[3][9] = res_9;
    result[3][10] = res_10;
    result[3][11] = res_11;
    result[3][12] = res_12;
    result[3][13] = res_13;
    result[3][14] = res_14;
    result[3][15] = res_15;


    opa_0 = wires[4][0];
    opa_1 = wires[4][1];
    opa_2 = wires[4][2];
    opa_3 = wires[4][3];
    opa_4 = wires[4][4];
    opa_5 = wires[4][5];
    opa_6 = wires[4][6];
    opa_7 = wires[4][7];
    opa_8 = wires[4][8];
    opa_9 = wires[4][9];
    opa_10 = wires[4][10];
    opa_11 = wires[4][11];
    opa_12 = wires[4][12];
    opa_13 = wires[4][13];
    opa_14 = wires[4][14];
    opa_15 = wires[4][15];

    opb_0 = wires_idx[4][0];
    opb_1 = wires_idx[4][1];
    opb_2 = wires_idx[4][2];
    opb_3 = wires_idx[4][3];
    opb_4 = wires_idx[4][4];
    opb_5 = wires_idx[4][5];
    opb_6 = wires_idx[4][6];
    opb_7 = wires_idx[4][7];
    opb_8 = wires_idx[4][8];
    opb_9 = wires_idx[4][9];
    opb_10 = wires_idx[4][10];
    opb_11 = wires_idx[4][11];
    opb_12 = wires_idx[4][12];
    opb_13 = wires_idx[4][13];
    opb_14 = wires_idx[4][14];
    opb_15 = wires_idx[4][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[4][0] = res_0;
    result[4][1] = res_1;
    result[4][2] = res_2;
    result[4][3] = res_3;
    result[4][4] = res_4;
    result[4][5] = res_5;
    result[4][6] = res_6;
    result[4][7] = res_7;
    result[4][8] = res_8;
    result[4][9] = res_9;
    result[4][10] = res_10;
    result[4][11] = res_11;
    result[4][12] = res_12;
    result[4][13] = res_13;
    result[4][14] = res_14;
    result[4][15] = res_15;


    opa_0 = wires[5][0];
    opa_1 = wires[5][1];
    opa_2 = wires[5][2];
    opa_3 = wires[5][3];
    opa_4 = wires[5][4];
    opa_5 = wires[5][5];
    opa_6 = wires[5][6];
    opa_7 = wires[5][7];
    opa_8 = wires[5][8];
    opa_9 = wires[5][9];
    opa_10 = wires[5][10];
    opa_11 = wires[5][11];
    opa_12 = wires[5][12];
    opa_13 = wires[5][13];
    opa_14 = wires[5][14];
    opa_15 = wires[5][15];

    opb_0 = wires_idx[5][0];
    opb_1 = wires_idx[5][1];
    opb_2 = wires_idx[5][2];
    opb_3 = wires_idx[5][3];
    opb_4 = wires_idx[5][4];
    opb_5 = wires_idx[5][5];
    opb_6 = wires_idx[5][6];
    opb_7 = wires_idx[5][7];
    opb_8 = wires_idx[5][8];
    opb_9 = wires_idx[5][9];
    opb_10 = wires_idx[5][10];
    opb_11 = wires_idx[5][11];
    opb_12 = wires_idx[5][12];
    opb_13 = wires_idx[5][13];
    opb_14 = wires_idx[5][14];
    opb_15 = wires_idx[5][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[5][0] = res_0;
    result[5][1] = res_1;
    result[5][2] = res_2;
    result[5][3] = res_3;
    result[5][4] = res_4;
    result[5][5] = res_5;
    result[5][6] = res_6;
    result[5][7] = res_7;
    result[5][8] = res_8;
    result[5][9] = res_9;
    result[5][10] = res_10;
    result[5][11] = res_11;
    result[5][12] = res_12;
    result[5][13] = res_13;
    result[5][14] = res_14;
    result[5][15] = res_15;


    opa_0 = wires[6][0];
    opa_1 = wires[6][1];
    opa_2 = wires[6][2];
    opa_3 = wires[6][3];
    opa_4 = wires[6][4];
    opa_5 = wires[6][5];
    opa_6 = wires[6][6];
    opa_7 = wires[6][7];
    opa_8 = wires[6][8];
    opa_9 = wires[6][9];
    opa_10 = wires[6][10];
    opa_11 = wires[6][11];
    opa_12 = wires[6][12];
    opa_13 = wires[6][13];
    opa_14 = wires[6][14];
    opa_15 = wires[6][15];

    opb_0 = wires_idx[6][0];
    opb_1 = wires_idx[6][1];
    opb_2 = wires_idx[6][2];
    opb_3 = wires_idx[6][3];
    opb_4 = wires_idx[6][4];
    opb_5 = wires_idx[6][5];
    opb_6 = wires_idx[6][6];
    opb_7 = wires_idx[6][7];
    opb_8 = wires_idx[6][8];
    opb_9 = wires_idx[6][9];
    opb_10 = wires_idx[6][10];
    opb_11 = wires_idx[6][11];
    opb_12 = wires_idx[6][12];
    opb_13 = wires_idx[6][13];
    opb_14 = wires_idx[6][14];
    opb_15 = wires_idx[6][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[6][0] = res_0;
    result[6][1] = res_1;
    result[6][2] = res_2;
    result[6][3] = res_3;
    result[6][4] = res_4;
    result[6][5] = res_5;
    result[6][6] = res_6;
    result[6][7] = res_7;
    result[6][8] = res_8;
    result[6][9] = res_9;
    result[6][10] = res_10;
    result[6][11] = res_11;
    result[6][12] = res_12;
    result[6][13] = res_13;
    result[6][14] = res_14;
    result[6][15] = res_15;


    opa_0 = wires[7][0];
    opa_1 = wires[7][1];
    opa_2 = wires[7][2];
    opa_3 = wires[7][3];
    opa_4 = wires[7][4];
    opa_5 = wires[7][5];
    opa_6 = wires[7][6];
    opa_7 = wires[7][7];
    opa_8 = wires[7][8];
    opa_9 = wires[7][9];
    opa_10 = wires[7][10];
    opa_11 = wires[7][11];
    opa_12 = wires[7][12];
    opa_13 = wires[7][13];
    opa_14 = wires[7][14];
    opa_15 = wires[7][15];

    opb_0 = wires_idx[7][0];
    opb_1 = wires_idx[7][1];
    opb_2 = wires_idx[7][2];
    opb_3 = wires_idx[7][3];
    opb_4 = wires_idx[7][4];
    opb_5 = wires_idx[7][5];
    opb_6 = wires_idx[7][6];
    opb_7 = wires_idx[7][7];
    opb_8 = wires_idx[7][8];
    opb_9 = wires_idx[7][9];
    opb_10 = wires_idx[7][10];
    opb_11 = wires_idx[7][11];
    opb_12 = wires_idx[7][12];
    opb_13 = wires_idx[7][13];
    opb_14 = wires_idx[7][14];
    opb_15 = wires_idx[7][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[7][0] = res_0;
    result[7][1] = res_1;
    result[7][2] = res_2;
    result[7][3] = res_3;
    result[7][4] = res_4;
    result[7][5] = res_5;
    result[7][6] = res_6;
    result[7][7] = res_7;
    result[7][8] = res_8;
    result[7][9] = res_9;
    result[7][10] = res_10;
    result[7][11] = res_11;
    result[7][12] = res_12;
    result[7][13] = res_13;
    result[7][14] = res_14;
    result[7][15] = res_15;


    opa_0 = wires[8][0];
    opa_1 = wires[8][1];
    opa_2 = wires[8][2];
    opa_3 = wires[8][3];
    opa_4 = wires[8][4];
    opa_5 = wires[8][5];
    opa_6 = wires[8][6];
    opa_7 = wires[8][7];
    opa_8 = wires[8][8];
    opa_9 = wires[8][9];
    opa_10 = wires[8][10];
    opa_11 = wires[8][11];
    opa_12 = wires[8][12];
    opa_13 = wires[8][13];
    opa_14 = wires[8][14];
    opa_15 = wires[8][15];

    opb_0 = wires_idx[8][0];
    opb_1 = wires_idx[8][1];
    opb_2 = wires_idx[8][2];
    opb_3 = wires_idx[8][3];
    opb_4 = wires_idx[8][4];
    opb_5 = wires_idx[8][5];
    opb_6 = wires_idx[8][6];
    opb_7 = wires_idx[8][7];
    opb_8 = wires_idx[8][8];
    opb_9 = wires_idx[8][9];
    opb_10 = wires_idx[8][10];
    opb_11 = wires_idx[8][11];
    opb_12 = wires_idx[8][12];
    opb_13 = wires_idx[8][13];
    opb_14 = wires_idx[8][14];
    opb_15 = wires_idx[8][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[8][0] = res_0;
    result[8][1] = res_1;
    result[8][2] = res_2;
    result[8][3] = res_3;
    result[8][4] = res_4;
    result[8][5] = res_5;
    result[8][6] = res_6;
    result[8][7] = res_7;
    result[8][8] = res_8;
    result[8][9] = res_9;
    result[8][10] = res_10;
    result[8][11] = res_11;
    result[8][12] = res_12;
    result[8][13] = res_13;
    result[8][14] = res_14;
    result[8][15] = res_15;


    opa_0 = wires[9][0];
    opa_1 = wires[9][1];
    opa_2 = wires[9][2];
    opa_3 = wires[9][3];
    opa_4 = wires[9][4];
    opa_5 = wires[9][5];
    opa_6 = wires[9][6];
    opa_7 = wires[9][7];
    opa_8 = wires[9][8];
    opa_9 = wires[9][9];
    opa_10 = wires[9][10];
    opa_11 = wires[9][11];
    opa_12 = wires[9][12];
    opa_13 = wires[9][13];
    opa_14 = wires[9][14];
    opa_15 = wires[9][15];

    opb_0 = wires_idx[9][0];
    opb_1 = wires_idx[9][1];
    opb_2 = wires_idx[9][2];
    opb_3 = wires_idx[9][3];
    opb_4 = wires_idx[9][4];
    opb_5 = wires_idx[9][5];
    opb_6 = wires_idx[9][6];
    opb_7 = wires_idx[9][7];
    opb_8 = wires_idx[9][8];
    opb_9 = wires_idx[9][9];
    opb_10 = wires_idx[9][10];
    opb_11 = wires_idx[9][11];
    opb_12 = wires_idx[9][12];
    opb_13 = wires_idx[9][13];
    opb_14 = wires_idx[9][14];
    opb_15 = wires_idx[9][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[9][0] = res_0;
    result[9][1] = res_1;
    result[9][2] = res_2;
    result[9][3] = res_3;
    result[9][4] = res_4;
    result[9][5] = res_5;
    result[9][6] = res_6;
    result[9][7] = res_7;
    result[9][8] = res_8;
    result[9][9] = res_9;
    result[9][10] = res_10;
    result[9][11] = res_11;
    result[9][12] = res_12;
    result[9][13] = res_13;
    result[9][14] = res_14;
    result[9][15] = res_15;


    opa_0 = wires[10][0];
    opa_1 = wires[10][1];
    opa_2 = wires[10][2];
    opa_3 = wires[10][3];
    opa_4 = wires[10][4];
    opa_5 = wires[10][5];
    opa_6 = wires[10][6];
    opa_7 = wires[10][7];
    opa_8 = wires[10][8];
    opa_9 = wires[10][9];
    opa_10 = wires[10][10];
    opa_11 = wires[10][11];
    opa_12 = wires[10][12];
    opa_13 = wires[10][13];
    opa_14 = wires[10][14];
    opa_15 = wires[10][15];

    opb_0 = wires_idx[10][0];
    opb_1 = wires_idx[10][1];
    opb_2 = wires_idx[10][2];
    opb_3 = wires_idx[10][3];
    opb_4 = wires_idx[10][4];
    opb_5 = wires_idx[10][5];
    opb_6 = wires_idx[10][6];
    opb_7 = wires_idx[10][7];
    opb_8 = wires_idx[10][8];
    opb_9 = wires_idx[10][9];
    opb_10 = wires_idx[10][10];
    opb_11 = wires_idx[10][11];
    opb_12 = wires_idx[10][12];
    opb_13 = wires_idx[10][13];
    opb_14 = wires_idx[10][14];
    opb_15 = wires_idx[10][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[10][0] = res_0;
    result[10][1] = res_1;
    result[10][2] = res_2;
    result[10][3] = res_3;
    result[10][4] = res_4;
    result[10][5] = res_5;
    result[10][6] = res_6;
    result[10][7] = res_7;
    result[10][8] = res_8;
    result[10][9] = res_9;
    result[10][10] = res_10;
    result[10][11] = res_11;
    result[10][12] = res_12;
    result[10][13] = res_13;
    result[10][14] = res_14;
    result[10][15] = res_15;


    opa_0 = wires[11][0];
    opa_1 = wires[11][1];
    opa_2 = wires[11][2];
    opa_3 = wires[11][3];
    opa_4 = wires[11][4];
    opa_5 = wires[11][5];
    opa_6 = wires[11][6];
    opa_7 = wires[11][7];
    opa_8 = wires[11][8];
    opa_9 = wires[11][9];
    opa_10 = wires[11][10];
    opa_11 = wires[11][11];
    opa_12 = wires[11][12];
    opa_13 = wires[11][13];
    opa_14 = wires[11][14];
    opa_15 = wires[11][15];

    opb_0 = wires_idx[11][0];
    opb_1 = wires_idx[11][1];
    opb_2 = wires_idx[11][2];
    opb_3 = wires_idx[11][3];
    opb_4 = wires_idx[11][4];
    opb_5 = wires_idx[11][5];
    opb_6 = wires_idx[11][6];
    opb_7 = wires_idx[11][7];
    opb_8 = wires_idx[11][8];
    opb_9 = wires_idx[11][9];
    opb_10 = wires_idx[11][10];
    opb_11 = wires_idx[11][11];
    opb_12 = wires_idx[11][12];
    opb_13 = wires_idx[11][13];
    opb_14 = wires_idx[11][14];
    opb_15 = wires_idx[11][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[11][0] = res_0;
    result[11][1] = res_1;
    result[11][2] = res_2;
    result[11][3] = res_3;
    result[11][4] = res_4;
    result[11][5] = res_5;
    result[11][6] = res_6;
    result[11][7] = res_7;
    result[11][8] = res_8;
    result[11][9] = res_9;
    result[11][10] = res_10;
    result[11][11] = res_11;
    result[11][12] = res_12;
    result[11][13] = res_13;
    result[11][14] = res_14;
    result[11][15] = res_15;

    opa_0 = wires[12][0];
    opa_1 = wires[12][1];
    opa_2 = wires[12][2];
    opa_3 = wires[12][3];
    opa_4 = wires[12][4];
    opa_5 = wires[12][5];
    opa_6 = wires[12][6];
    opa_7 = wires[12][7];
    opa_8 = wires[12][8];
    opa_9 = wires[12][9];
    opa_10 = wires[12][10];
    opa_11 = wires[12][11];
    opa_12 = wires[12][12];
    opa_13 = wires[12][13];
    opa_14 = wires[12][14];
    opa_15 = wires[12][15];

    opb_0 = wires_idx[12][0];
    opb_1 = wires_idx[12][1];
    opb_2 = wires_idx[12][2];
    opb_3 = wires_idx[12][3];
    opb_4 = wires_idx[12][4];
    opb_5 = wires_idx[12][5];
    opb_6 = wires_idx[12][6];
    opb_7 = wires_idx[12][7];
    opb_8 = wires_idx[12][8];
    opb_9 = wires_idx[12][9];
    opb_10 = wires_idx[12][10];
    opb_11 = wires_idx[12][11];
    opb_12 = wires_idx[12][12];
    opb_13 = wires_idx[12][13];
    opb_14 = wires_idx[12][14];
    opb_15 = wires_idx[12][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[12][0] = res_0;
    result[12][1] = res_1;
    result[12][2] = res_2;
    result[12][3] = res_3;
    result[12][4] = res_4;
    result[12][5] = res_5;
    result[12][6] = res_6;
    result[12][7] = res_7;
    result[12][8] = res_8;
    result[12][9] = res_9;
    result[12][10] = res_10;
    result[12][11] = res_11;
    result[12][12] = res_12;
    result[12][13] = res_13;
    result[12][14] = res_14;
    result[12][15] = res_15;


    opa_0 = wires[13][0];
    opa_1 = wires[13][1];
    opa_2 = wires[13][2];
    opa_3 = wires[13][3];
    opa_4 = wires[13][4];
    opa_5 = wires[13][5];
    opa_6 = wires[13][6];
    opa_7 = wires[13][7];
    opa_8 = wires[13][8];
    opa_9 = wires[13][9];
    opa_10 = wires[13][10];
    opa_11 = wires[13][11];
    opa_12 = wires[13][12];
    opa_13 = wires[13][13];
    opa_14 = wires[13][14];
    opa_15 = wires[13][15];

    opb_0 = wires_idx[13][0];
    opb_1 = wires_idx[13][1];
    opb_2 = wires_idx[13][2];
    opb_3 = wires_idx[13][3];
    opb_4 = wires_idx[13][4];
    opb_5 = wires_idx[13][5];
    opb_6 = wires_idx[13][6];
    opb_7 = wires_idx[13][7];
    opb_8 = wires_idx[13][8];
    opb_9 = wires_idx[13][9];
    opb_10 = wires_idx[13][10];
    opb_11 = wires_idx[13][11];
    opb_12 = wires_idx[13][12];
    opb_13 = wires_idx[13][13];
    opb_14 = wires_idx[13][14];
    opb_15 = wires_idx[13][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[13][0] = res_0;
    result[13][1] = res_1;
    result[13][2] = res_2;
    result[13][3] = res_3;
    result[13][4] = res_4;
    result[13][5] = res_5;
    result[13][6] = res_6;
    result[13][7] = res_7;
    result[13][8] = res_8;
    result[13][9] = res_9;
    result[13][10] = res_10;
    result[13][11] = res_11;
    result[13][12] = res_12;
    result[13][13] = res_13;
    result[13][14] = res_14;
    result[13][15] = res_15;


    opa_0 = wires[14][0];
    opa_1 = wires[14][1];
    opa_2 = wires[14][2];
    opa_3 = wires[14][3];
    opa_4 = wires[14][4];
    opa_5 = wires[14][5];
    opa_6 = wires[14][6];
    opa_7 = wires[14][7];
    opa_8 = wires[14][8];
    opa_9 = wires[14][9];
    opa_10 = wires[14][10];
    opa_11 = wires[14][11];
    opa_12 = wires[14][12];
    opa_13 = wires[14][13];
    opa_14 = wires[14][14];
    opa_15 = wires[14][15];

    opb_0 = wires_idx[14][0];
    opb_1 = wires_idx[14][1];
    opb_2 = wires_idx[14][2];
    opb_3 = wires_idx[14][3];
    opb_4 = wires_idx[14][4];
    opb_5 = wires_idx[14][5];
    opb_6 = wires_idx[14][6];
    opb_7 = wires_idx[14][7];
    opb_8 = wires_idx[14][8];
    opb_9 = wires_idx[14][9];
    opb_10 = wires_idx[14][10];
    opb_11 = wires_idx[14][11];
    opb_12 = wires_idx[14][12];
    opb_13 = wires_idx[14][13];
    opb_14 = wires_idx[14][14];
    opb_15 = wires_idx[14][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[14][0] = res_0;
    result[14][1] = res_1;
    result[14][2] = res_2;
    result[14][3] = res_3;
    result[14][4] = res_4;
    result[14][5] = res_5;
    result[14][6] = res_6;
    result[14][7] = res_7;
    result[14][8] = res_8;
    result[14][9] = res_9;
    result[14][10] = res_10;
    result[14][11] = res_11;
    result[14][12] = res_12;
    result[14][13] = res_13;
    result[14][14] = res_14;
    result[14][15] = res_15;


    opa_0 = wires[15][0];
    opa_1 = wires[15][1];
    opa_2 = wires[15][2];
    opa_3 = wires[15][3];
    opa_4 = wires[15][4];
    opa_5 = wires[15][5];
    opa_6 = wires[15][6];
    opa_7 = wires[15][7];
    opa_8 = wires[15][8];
    opa_9 = wires[15][9];
    opa_10 = wires[15][10];
    opa_11 = wires[15][11];
    opa_12 = wires[15][12];
    opa_13 = wires[15][13];
    opa_14 = wires[15][14];
    opa_15 = wires[15][15];

    opb_0 = wires_idx[15][0];
    opb_1 = wires_idx[15][1];
    opb_2 = wires_idx[15][2];
    opb_3 = wires_idx[15][3];
    opb_4 = wires_idx[15][4];
    opb_5 = wires_idx[15][5];
    opb_6 = wires_idx[15][6];
    opb_7 = wires_idx[15][7];
    opb_8 = wires_idx[15][8];
    opb_9 = wires_idx[15][9];
    opb_10 = wires_idx[15][10];
    opb_11 = wires_idx[15][11];
    opb_12 = wires_idx[15][12];
    opb_13 = wires_idx[15][13];
    opb_14 = wires_idx[15][14];
    opb_15 = wires_idx[15][15];

    res_0 = opa_0 + opb_0;
    res_1 = opa_1 + opb_1;
    res_2 = opa_2 + opb_2;
    res_3 = opa_3 + opb_3;
    res_4 = opa_4 + opb_4;
    res_5 = opa_5 + opb_5;
    res_6 = opa_6 + opb_6;
    res_7 = opa_7 + opb_7;
    res_8 = opa_8 + opb_8;
    res_9 = opa_9 + opb_9;
    res_10 = opa_10 + opb_10;
    res_11 = opa_11 + opb_11;
    res_12 = opa_12 + opb_12;
    res_13 = opa_13 + opb_13;
    res_14 = opa_14 + opb_14;
    res_15 = opa_15 + opb_15;

    result[15][0] = res_0;
    result[15][1] = res_1;
    result[15][2] = res_2;
    result[15][3] = res_3;
    result[15][4] = res_4;
    result[15][5] = res_5;
    result[15][6] = res_6;
    result[15][7] = res_7;
    result[15][8] = res_8;
    result[15][9] = res_9;
    result[15][10] = res_10;
    result[15][11] = res_11;
    result[15][12] = res_12;
    result[15][13] = res_13;
    result[15][14] = res_14;
    result[15][15] = res_15;*/

    /*result[0][0] = wires[0][0] + wires_idx[0][0];
    result[0][1] = wires[0][1] + wires_idx[0][1];
    result[0][2] = wires[0][2] + wires_idx[0][2];
    result[0][3] = wires[0][3] + wires_idx[0][3];
    result[0][4] = wires[0][4] + wires_idx[0][4];
    result[0][5] = wires[0][5] + wires_idx[0][5];
    result[0][6] = wires[0][6] + wires_idx[0][6];
    result[0][7] = wires[0][7] + wires_idx[0][7];
    result[0][8] = wires[0][8] + wires_idx[0][8];
    result[0][9] = wires[0][9] + wires_idx[0][9];
    result[0][10] = wires[0][10] + wires_idx[0][10];
    result[0][11] = wires[0][11] + wires_idx[0][11];
    result[0][12] = wires[0][12] + wires_idx[0][12];
    result[0][13] = wires[0][13] + wires_idx[0][13];
    result[0][14] = wires[0][14] + wires_idx[0][14];
    result[0][15] = wires[0][15] + wires_idx[0][15];

    result[1][0] = wires[1][0] + wires_idx[1][0];
    result[1][1] = wires[1][1] + wires_idx[1][1];
    result[1][2] = wires[1][2] + wires_idx[1][2];
    result[1][3] = wires[1][3] + wires_idx[1][3];
    result[1][4] = wires[1][4] + wires_idx[1][4];
    result[1][5] = wires[1][5] + wires_idx[1][5];
    result[1][6] = wires[1][6] + wires_idx[1][6];
    result[1][7] = wires[1][7] + wires_idx[1][7];
    result[1][8] = wires[1][8] + wires_idx[1][8];
    result[1][9] = wires[1][9] + wires_idx[1][9];
    result[1][10] = wires[1][10] + wires_idx[1][10];
    result[1][11] = wires[1][11] + wires_idx[1][11];
    result[1][12] = wires[1][12] + wires_idx[1][12];
    result[1][13] = wires[1][13] + wires_idx[1][13];
    result[1][14] = wires[1][14] + wires_idx[1][14];
    result[1][15] = wires[1][15] + wires_idx[1][15];

    result[2][0] = wires[2][0] + wires_idx[2][0];
    result[2][1] = wires[2][1] + wires_idx[2][1];
    result[2][2] = wires[2][2] + wires_idx[2][2];
    result[2][3] = wires[2][3] + wires_idx[2][3];
    result[2][4] = wires[2][4] + wires_idx[2][4];
    result[2][5] = wires[2][5] + wires_idx[2][5];
    result[2][6] = wires[2][6] + wires_idx[2][6];
    result[2][7] = wires[2][7] + wires_idx[2][7];
    result[2][8] = wires[2][8] + wires_idx[2][8];
    result[2][9] = wires[2][9] + wires_idx[2][9];
    result[2][10] = wires[2][10] + wires_idx[2][10];
    result[2][11] = wires[2][11] + wires_idx[2][11];
    result[2][12] = wires[2][12] + wires_idx[2][12];
    result[2][13] = wires[2][13] + wires_idx[2][13];
    result[2][14] = wires[2][14] + wires_idx[2][14];
    result[2][15] = wires[2][15] + wires_idx[2][15];

    result[3][0] = wires[3][0] + wires_idx[3][0];
    result[3][1] = wires[3][1] + wires_idx[3][1];
    result[3][2] = wires[3][2] + wires_idx[3][2];
    result[3][3] = wires[3][3] + wires_idx[3][3];
    result[3][4] = wires[3][4] + wires_idx[3][4];
    result[3][5] = wires[3][5] + wires_idx[3][5];
    result[3][6] = wires[3][6] + wires_idx[3][6];
    result[3][7] = wires[3][7] + wires_idx[3][7];
    result[3][8] = wires[3][8] + wires_idx[3][8];
    result[3][9] = wires[3][9] + wires_idx[3][9];
    result[3][10] = wires[3][10] + wires_idx[3][10];
    result[3][11] = wires[3][11] + wires_idx[3][11];
    result[3][12] = wires[3][12] + wires_idx[3][12];
    result[3][13] = wires[3][13] + wires_idx[3][13];
    result[3][14] = wires[3][14] + wires_idx[3][14];
    result[3][15] = wires[3][15] + wires_idx[3][15];

    result[4][0] = wires[4][0] + wires_idx[4][0];
    result[4][1] = wires[4][1] + wires_idx[4][1];
    result[4][2] = wires[4][2] + wires_idx[4][2];
    result[4][3] = wires[4][3] + wires_idx[4][3];
    result[4][4] = wires[4][4] + wires_idx[4][4];
    result[4][5] = wires[4][5] + wires_idx[4][5];
    result[4][6] = wires[4][6] + wires_idx[4][6];
    result[4][7] = wires[4][7] + wires_idx[4][7];
    result[4][8] = wires[4][8] + wires_idx[4][8];
    result[4][9] = wires[4][9] + wires_idx[4][9];
    result[4][10] = wires[4][10] + wires_idx[4][10];
    result[4][11] = wires[4][11] + wires_idx[4][11];
    result[4][12] = wires[4][12] + wires_idx[4][12];
    result[4][13] = wires[4][13] + wires_idx[4][13];
    result[4][14] = wires[4][14] + wires_idx[4][14];
    result[4][15] = wires[4][15] + wires_idx[4][15];

    result[5][0] = wires[5][0] + wires_idx[5][0];
    result[5][1] = wires[5][1] + wires_idx[5][1];
    result[5][2] = wires[5][2] + wires_idx[5][2];
    result[5][3] = wires[5][3] + wires_idx[5][3];
    result[5][4] = wires[5][4] + wires_idx[5][4];
    result[5][5] = wires[5][5] + wires_idx[5][5];
    result[5][6] = wires[5][6] + wires_idx[5][6];
    result[5][7] = wires[5][7] + wires_idx[5][7];
    result[5][8] = wires[5][8] + wires_idx[5][8];
    result[5][9] = wires[5][9] + wires_idx[5][9];
    result[5][10] = wires[5][10] + wires_idx[5][10];
    result[5][11] = wires[5][11] + wires_idx[5][11];
    result[5][12] = wires[5][12] + wires_idx[5][12];
    result[5][13] = wires[5][13] + wires_idx[5][13];
    result[5][14] = wires[5][14] + wires_idx[5][14];
    result[5][15] = wires[5][15] + wires_idx[5][15];

    result[6][0] = wires[6][0] + wires_idx[6][0];
    result[6][1] = wires[6][1] + wires_idx[6][1];
    result[6][2] = wires[6][2] + wires_idx[6][2];
    result[6][3] = wires[6][3] + wires_idx[6][3];
    result[6][4] = wires[6][4] + wires_idx[6][4];
    result[6][5] = wires[6][5] + wires_idx[6][5];
    result[6][6] = wires[6][6] + wires_idx[6][6];
    result[6][7] = wires[6][7] + wires_idx[6][7];
    result[6][8] = wires[6][8] + wires_idx[6][8];
    result[6][9] = wires[6][9] + wires_idx[6][9];
    result[6][10] = wires[6][10] + wires_idx[6][10];
    result[6][11] = wires[6][11] + wires_idx[6][11];
    result[6][12] = wires[6][12] + wires_idx[6][12];
    result[6][13] = wires[6][13] + wires_idx[6][13];
    result[6][14] = wires[6][14] + wires_idx[6][14];
    result[6][15] = wires[6][15] + wires_idx[6][15];

    result[7][0] = wires[7][0] + wires_idx[7][0];
    result[7][1] = wires[7][1] + wires_idx[7][1];
    result[7][2] = wires[7][2] + wires_idx[7][2];
    result[7][3] = wires[7][3] + wires_idx[7][3];
    result[7][4] = wires[7][4] + wires_idx[7][4];
    result[7][5] = wires[7][5] + wires_idx[7][5];
    result[7][6] = wires[7][6] + wires_idx[7][6];
    result[7][7] = wires[7][7] + wires_idx[7][7];
    result[7][8] = wires[7][8] + wires_idx[7][8];
    result[7][9] = wires[7][9] + wires_idx[7][9];
    result[7][10] = wires[7][10] + wires_idx[7][10];
    result[7][11] = wires[7][11] + wires_idx[7][11];
    result[7][12] = wires[7][12] + wires_idx[7][12];
    result[7][13] = wires[7][13] + wires_idx[7][13];
    result[7][14] = wires[7][14] + wires_idx[7][14];
    result[7][15] = wires[7][15] + wires_idx[7][15];

    result[8][0] = wires[8][0] + wires_idx[8][0];
    result[8][1] = wires[8][1] + wires_idx[8][1];
    result[8][2] = wires[8][2] + wires_idx[8][2];
    result[8][3] = wires[8][3] + wires_idx[8][3];
    result[8][4] = wires[8][4] + wires_idx[8][4];
    result[8][5] = wires[8][5] + wires_idx[8][5];
    result[8][6] = wires[8][6] + wires_idx[8][6];
    result[8][7] = wires[8][7] + wires_idx[8][7];
    result[8][8] = wires[8][8] + wires_idx[8][8];
    result[8][9] = wires[8][9] + wires_idx[8][9];
    result[8][10] = wires[8][10] + wires_idx[8][10];
    result[8][11] = wires[8][11] + wires_idx[8][11];
    result[8][12] = wires[8][12] + wires_idx[8][12];
    result[8][13] = wires[8][13] + wires_idx[8][13];
    result[8][14] = wires[8][14] + wires_idx[8][14];
    result[8][15] = wires[8][15] + wires_idx[8][15];

    result[9][0] = wires[9][0] + wires_idx[9][0];
    result[9][1] = wires[9][1] + wires_idx[9][1];
    result[9][2] = wires[9][2] + wires_idx[9][2];
    result[9][3] = wires[9][3] + wires_idx[9][3];
    result[9][4] = wires[9][4] + wires_idx[9][4];
    result[9][5] = wires[9][5] + wires_idx[9][5];
    result[9][6] = wires[9][6] + wires_idx[9][6];
    result[9][7] = wires[9][7] + wires_idx[9][7];
    result[9][8] = wires[9][8] + wires_idx[9][8];
    result[9][9] = wires[9][9] + wires_idx[9][9];
    result[9][10] = wires[9][10] + wires_idx[9][10];
    result[9][11] = wires[9][11] + wires_idx[9][11];
    result[9][12] = wires[9][12] + wires_idx[9][12];
    result[9][13] = wires[9][13] + wires_idx[9][13];
    result[9][14] = wires[9][14] + wires_idx[9][14];
    result[9][15] = wires[9][15] + wires_idx[9][15];

    result[10][0] = wires[10][0] + wires_idx[10][0];
    result[10][1] = wires[10][1] + wires_idx[10][1];
    result[10][2] = wires[10][2] + wires_idx[10][2];
    result[10][3] = wires[10][3] + wires_idx[10][3];
    result[10][4] = wires[10][4] + wires_idx[10][4];
    result[10][5] = wires[10][5] + wires_idx[10][5];
    result[10][6] = wires[10][6] + wires_idx[10][6];
    result[10][7] = wires[10][7] + wires_idx[10][7];
    result[10][8] = wires[10][8] + wires_idx[10][8];
    result[10][9] = wires[10][9] + wires_idx[10][9];
    result[10][10] = wires[10][10] + wires_idx[10][10];
    result[10][11] = wires[10][11] + wires_idx[10][11];
    result[10][12] = wires[10][12] + wires_idx[10][12];
    result[10][13] = wires[10][13] + wires_idx[10][13];
    result[10][14] = wires[10][14] + wires_idx[10][14];
    result[10][15] = wires[10][15] + wires_idx[10][15];

    result[11][0] = wires[11][0] + wires_idx[11][0];
    result[11][1] = wires[11][1] + wires_idx[11][1];
    result[11][2] = wires[11][2] + wires_idx[11][2];
    result[11][3] = wires[11][3] + wires_idx[11][3];
    result[11][4] = wires[11][4] + wires_idx[11][4];
    result[11][5] = wires[11][5] + wires_idx[11][5];
    result[11][6] = wires[11][6] + wires_idx[11][6];
    result[11][7] = wires[11][7] + wires_idx[11][7];
    result[11][8] = wires[11][8] + wires_idx[11][8];
    result[11][9] = wires[11][9] + wires_idx[11][9];
    result[11][10] = wires[11][10] + wires_idx[11][10];
    result[11][11] = wires[11][11] + wires_idx[11][11];
    result[11][12] = wires[11][12] + wires_idx[11][12];
    result[11][13] = wires[11][13] + wires_idx[11][13];
    result[11][14] = wires[11][14] + wires_idx[11][14];
    result[11][15] = wires[11][15] + wires_idx[11][15];

    result[12][0] = wires[12][0] + wires_idx[12][0];
    result[12][1] = wires[12][1] + wires_idx[12][1];
    result[12][2] = wires[12][2] + wires_idx[12][2];
    result[12][3] = wires[12][3] + wires_idx[12][3];
    result[12][4] = wires[12][4] + wires_idx[12][4];
    result[12][5] = wires[12][5] + wires_idx[12][5];
    result[12][6] = wires[12][6] + wires_idx[12][6];
    result[12][7] = wires[12][7] + wires_idx[12][7];
    result[12][8] = wires[12][8] + wires_idx[12][8];
    result[12][9] = wires[12][9] + wires_idx[12][9];
    result[12][10] = wires[12][10] + wires_idx[12][10];
    result[12][11] = wires[12][11] + wires_idx[12][11];
    result[12][12] = wires[12][12] + wires_idx[12][12];
    result[12][13] = wires[12][13] + wires_idx[12][13];
    result[12][14] = wires[12][14] + wires_idx[12][14];
    result[12][15] = wires[12][15] + wires_idx[12][15];

    result[13][0] = wires[13][0] + wires_idx[13][0];
    result[13][1] = wires[13][1] + wires_idx[13][1];
    result[13][2] = wires[13][2] + wires_idx[13][2];
    result[13][3] = wires[13][3] + wires_idx[13][3];
    result[13][4] = wires[13][4] + wires_idx[13][4];
    result[13][5] = wires[13][5] + wires_idx[13][5];
    result[13][6] = wires[13][6] + wires_idx[13][6];
    result[13][7] = wires[13][7] + wires_idx[13][7];
    result[13][8] = wires[13][8] + wires_idx[13][8];
    result[13][9] = wires[13][9] + wires_idx[13][9];
    result[13][10] = wires[13][10] + wires_idx[13][10];
    result[13][11] = wires[13][11] + wires_idx[13][11];
    result[13][12] = wires[13][12] + wires_idx[13][12];
    result[13][13] = wires[13][13] + wires_idx[13][13];
    result[13][14] = wires[13][14] + wires_idx[13][14];
    result[13][15] = wires[13][15] + wires_idx[13][15];

    result[14][0] = wires[14][0] + wires_idx[14][0];
    result[14][1] = wires[14][1] + wires_idx[14][1];
    result[14][2] = wires[14][2] + wires_idx[14][2];
    result[14][3] = wires[14][3] + wires_idx[14][3];
    result[14][4] = wires[14][4] + wires_idx[14][4];
    result[14][5] = wires[14][5] + wires_idx[14][5];
    result[14][6] = wires[14][6] + wires_idx[14][6];
    result[14][7] = wires[14][7] + wires_idx[14][7];
    result[14][8] = wires[14][8] + wires_idx[14][8];
    result[14][9] = wires[14][9] + wires_idx[14][9];
    result[14][10] = wires[14][10] + wires_idx[14][10];
    result[14][11] = wires[14][11] + wires_idx[14][11];
    result[14][12] = wires[14][12] + wires_idx[14][12];
    result[14][13] = wires[14][13] + wires_idx[14][13];
    result[14][14] = wires[14][14] + wires_idx[14][14];
    result[14][15] = wires[14][15] + wires_idx[14][15];

    result[15][0] = wires[15][0] + wires_idx[15][0];
    result[15][1] = wires[15][1] + wires_idx[15][1];
    result[15][2] = wires[15][2] + wires_idx[15][2];
    result[15][3] = wires[15][3] + wires_idx[15][3];
    result[15][4] = wires[15][4] + wires_idx[15][4];
    result[15][5] = wires[15][5] + wires_idx[15][5];
    result[15][6] = wires[15][6] + wires_idx[15][6];
    result[15][7] = wires[15][7] + wires_idx[15][7];
    result[15][8] = wires[15][8] + wires_idx[15][8];
    result[15][9] = wires[15][9] + wires_idx[15][9];
    result[15][10] = wires[15][10] + wires_idx[15][10];
    result[15][11] = wires[15][11] + wires_idx[15][11];
    result[15][12] = wires[15][12] + wires_idx[15][12];
    result[15][13] = wires[15][13] + wires_idx[15][13];
    result[15][14] = wires[15][14] + wires_idx[15][14];
    result[15][15] = wires[15][15] + wires_idx[15][15];*/
    /*
    for (i=0; i<q_field; i++)
        for (j=0; j<q_field; j++)
            result[i][j] = wires[i][j] + wires_idx[i][j];*/

    /*for (i=0; i<q_field; i++){
        asm volatile("vle64.v v0, (%0);" ::"r"(&wires[i][0])); 
        asm volatile("vle64.v v1, (%0);" ::"r"(&wires_idx[i][0])); 
        asm volatile("vadd.vv v3, v0, v1;");
        asm volatile("vse64.v v3, (%0);" ::"r"(&result[i][0]));
    }*/

    asm volatile("vle64.v v0, (%0);" ::"r"(&wires[0][0])); 
    asm volatile("vle64.v v1, (%0);" ::"r"(&wires[1][0])); 
    asm volatile("vle64.v v2, (%0);" ::"r"(&wires[2][0])); 
    asm volatile("vle64.v v3, (%0);" ::"r"(&wires[3][0])); 
    asm volatile("vle64.v v4, (%0);" ::"r"(&wires[4][0])); 
    asm volatile("vle64.v v5, (%0);" ::"r"(&wires[5][0])); 
    asm volatile("vle64.v v6, (%0);" ::"r"(&wires[6][0])); 
    asm volatile("vle64.v v7, (%0);" ::"r"(&wires[7][0])); 

    asm volatile("vle64.v v8, (%0);" ::"r"(&wires_idx[0][0])); 
    asm volatile("vle64.v v9, (%0);" ::"r"(&wires_idx[1][0])); 
    asm volatile("vle64.v v10, (%0);" ::"r"(&wires_idx[2][0])); 
    asm volatile("vle64.v v11, (%0);" ::"r"(&wires_idx[3][0])); 
    asm volatile("vle64.v v12, (%0);" ::"r"(&wires_idx[4][0])); 
    asm volatile("vle64.v v13, (%0);" ::"r"(&wires_idx[5][0])); 
    asm volatile("vle64.v v14, (%0);" ::"r"(&wires_idx[6][0])); 
    asm volatile("vle64.v v15, (%0);" ::"r"(&wires_idx[7][0])); 

    asm volatile("vadd.vv v16, v0, v8;");
    asm volatile("vadd.vv v17, v1, v9;");
    asm volatile("vadd.vv v18, v2, v10;");
    asm volatile("vadd.vv v19, v3, v11;");
    asm volatile("vadd.vv v20, v4, v12;");
    asm volatile("vadd.vv v21, v5, v13;");
    asm volatile("vadd.vv v22, v6, v14;");
    asm volatile("vadd.vv v23, v7, v15;");

    asm volatile("vse64.v v16, (%0);" ::"r"(&result[0][0]));
    asm volatile("vse64.v v17, (%0);" ::"r"(&result[1][0]));
    asm volatile("vse64.v v18, (%0);" ::"r"(&result[2][0]));
    asm volatile("vse64.v v19, (%0);" ::"r"(&result[3][0]));
    asm volatile("vse64.v v20, (%0);" ::"r"(&result[4][0]));
    asm volatile("vse64.v v21, (%0);" ::"r"(&result[5][0]));
    asm volatile("vse64.v v22, (%0);" ::"r"(&result[6][0]));
    asm volatile("vse64.v v23, (%0);" ::"r"(&result[7][0]));


    asm volatile("vle64.v v0, (%0);" ::"r"(&wires[8][0])); 
    asm volatile("vle64.v v1, (%0);" ::"r"(&wires[9][0])); 
    asm volatile("vle64.v v2, (%0);" ::"r"(&wires[10][0])); 
    asm volatile("vle64.v v3, (%0);" ::"r"(&wires[11][0])); 
    asm volatile("vle64.v v4, (%0);" ::"r"(&wires[12][0])); 
    asm volatile("vle64.v v5, (%0);" ::"r"(&wires[13][0])); 
    asm volatile("vle64.v v6, (%0);" ::"r"(&wires[14][0])); 
    asm volatile("vle64.v v7, (%0);" ::"r"(&wires[15][0])); 

    asm volatile("vle64.v v8, (%0);" ::"r"(&wires_idx[8][0])); 
    asm volatile("vle64.v v9, (%0);" ::"r"(&wires_idx[9][0])); 
    asm volatile("vle64.v v10, (%0);" ::"r"(&wires_idx[10][0])); 
    asm volatile("vle64.v v11, (%0);" ::"r"(&wires_idx[11][0])); 
    asm volatile("vle64.v v12, (%0);" ::"r"(&wires_idx[12][0])); 
    asm volatile("vle64.v v13, (%0);" ::"r"(&wires_idx[13][0])); 
    asm volatile("vle64.v v14, (%0);" ::"r"(&wires_idx[14][0])); 
    asm volatile("vle64.v v15, (%0);" ::"r"(&wires_idx[15][0])); 

    asm volatile("vadd.vv v16, v0, v8;");
    asm volatile("vadd.vv v17, v1, v9;");
    asm volatile("vadd.vv v18, v2, v10;");
    asm volatile("vadd.vv v19, v3, v11;");
    asm volatile("vadd.vv v20, v4, v12;");
    asm volatile("vadd.vv v21, v5, v13;");
    asm volatile("vadd.vv v22, v6, v14;");
    asm volatile("vadd.vv v23, v7, v15;");

    asm volatile("vse64.v v16, (%0);" ::"r"(&result[8][0]));
    asm volatile("vse64.v v17, (%0);" ::"r"(&result[9][0]));
    asm volatile("vse64.v v18, (%0);" ::"r"(&result[10][0]));
    asm volatile("vse64.v v19, (%0);" ::"r"(&result[11][0]));
    asm volatile("vse64.v v20, (%0);" ::"r"(&result[12][0]));
    asm volatile("vse64.v v21, (%0);" ::"r"(&result[13][0]));
    asm volatile("vse64.v v22, (%0);" ::"r"(&result[14][0]));
    asm volatile("vse64.v v23, (%0);" ::"r"(&result[15][0]));
    stop_timer();
    cycles = get_timer();

    for (i=0; i<q_field; i++)
        for (j=0; j<q_field; j++)
            if(result[i][j] != golden[i][j])
                error = 1;
    
    if(error ==1)
        printf("ERROR\n");
    else 
        printf("SUCCESS\n");

    printf("--------------------------------------\n");
    printf("--------------------------------------\n");
    printf("Base instruction set: \t%d cycles.\n", cycles);
    printf("--------------------------------------\n");
    printf("--------------------------------------\n");         

  return 0;
}
