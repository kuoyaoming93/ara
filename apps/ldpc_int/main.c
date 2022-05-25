#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "printf.h"
#include "runtime.h"


#include "constantes_CONF.h"
#include "gf_tables_GF16.h"
#include "CNU_tables_GF16.h"
#include "Hmat_N32_M16_GF16.h"

//#define VECTOR_EXT
#define FOR_BACK

//#include "input.h"

int64_t Ln_aux[16][32] = {
    {6,2,7,0,5,0,3,2,11,4,0,1,6,5,3,4,6,7,9,1,5,12,2,1,12,3,3,2,2,4,4,5},
    {0,0,9,0,4,2,6,3,7,7,3,5,2,2,6,6,5,6,6,0,3,9,3,3,8,0,4,6,6,2,8,1},
    {9,1,4,3,3,0,0,4,6,2,2,3,5,8,4,0,10,4,5,4,4,9,1,0,8,4,5,5,1,2,3,4}, 
    {8,2,5,0,9,3,3,2,9,2,1,2,4,8,2,7,3,6,6,5,7,8,2,4,13,3,1,0,6,7,4,9}, 
    {6,6,5,0,3,3,6,0,10,4,0,0,8,3,0,7,3,4,10,1,3,10,1,2,7,8,1,6,0,6,2,4}, 
    {3,0,6,3,2,1,3,5,2,5,4,7,1,5,7,1,9,3,2,3,2,6,1,1,4,0,6,9,5,0,6,1}, 
    {11,2,1,3,7,2,0,4,4,0,3,4,3,11,3,2,8,3,2,7,5,5,0,2,9,3,3,2,5,4,2,8}, 
    {8,7,3,1,7,6,6,0,8,2,1,1,6,6,0,10,1,3,7,4,5,6,1,5,8,8,0,4,4,9,1,8}, 
    {2,4,4,3,0,4,6,3,1,5,4,5,3,3,4,4,7,0,3,2,0,4,1,2,0,6,4,13,3,1,4,0}, 
    {1,1,7,0,7,4,6,2,5,5,4,6,0,5,5,9,2,5,3,3,5,5,2,6,9,0,2,4,9,4,7,5}, 
    {9,6,2,4,1,2,2,2,5,2,1,2,7,6,1,2,8,1,6,3,1,7,0,0,3,9,3,9,0,4,0,3}, 
    {4,0,3,3,6,3,3,4,0,3,5,8,0,8,6,4,7,2,0,6,3,2,1,4,5,0,4,7,9,2,5,4}, 
    {10,6,0,4,5,5,2,2,3,0,2,3,5,9,0,5,5,0,4,6,3,3,0,3,4,8,2,6,3,6,0,7}, 
    {4,4,2,4,3,6,6,2,0,3,5,7,2,6,3,7,4,0,1,5,1,0,0,5,0,5,3,11,7,4,3,3}, 
    {1,5,5,1,5,7,9,0,4,5,3,5,3,3,3,12,0,2,4,3,3,3,2,7,4,5,0,8,8,6,5,4}, 
    {0,4,7,0,1,5,9,0,6,7,2,3,4,0,3,9,2,3,7,0,1,7,2,4,3,5,2,11,4,4,6,0}
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

int main(void)
{   
    int i,j,k,var,row; /* Used for loop indexs */

    int64_t 	decoded[N_code][m_field];
    //float 	r_ch[N_code][m_field];
    //float 	Ln_aux[q_field][N_code];
    int64_t 	Rmn_SRL[M_code][q_field][dc];

    int64_t Qmn[q_field][dc];
    int64_t Qmn_temp[q_field];

    int64_t aux1, aux2;
    int64_t MAX_temp; //MAX_temp2;

    int64_t beta;
    int64_t z[dc];
          
    int64_t Rmn[q_field][dc];
    int64_t Qn_NEW[q_field][dc];

    int64_t H_decoded[it_max];
    int MNBE_Hdecoded[it_max];
    int MNPE_Hdecoded[it_max];

#ifndef FOR_BACK
    int64_t min_temp;
	int64_t min_temp2;
    int64_t min1[q_field], min2[q_field];
    int64_t cam1[q_field], cam2[q_field];
    int64_t dQ_min1, dQ_min2; 
    int64_t dQ_pos1, dQ_pos2;
    int64_t dWmn[q_field][dc];
    int64_t temp[q_field][dc];
    int64_t pos[q_field];
    int64_t cam1_temp[q_field/2 - 1], cam2_temp[q_field/2 - 1];
    int64_t min_global[q_field]; //min2_global[q_field];  
    int64_t oRmn_temp;
    int64_t pos_temp;
    int64_t max[q_field/2];
#endif    
	
#ifdef FOR_BACK
	int a;
	int64_t R_Forward[q_field][dc], R_Backward[q_field][dc];
    int64_t R_compare[q_field], R_compare_2[q_field];
    int64_t min_temp, min_temp_2, min_temp_3;
#endif    

    //int error = 0;

    /*printf("LLR Function: ");
    for (i = 0; i< q_field; i++){
        for(j=0; j<N_code;j++)
            printf("%f, \n",Ln_aux[i][j]);
        printf("\n");
    }*/

    printf("Hola! \n");
    unsigned long int block_size_p;
    // Set the vector configuration
    asm volatile("vsetvli %0, %1, e64, m2, ta, ma" : "=r"(block_size_p) : "r"(q_field));

    /* Inicialize Rmn_SRL to zero values */
    for (i = 0; i<M_code; i++)
        for (j=0; j<q_field; j++)
            for (k=0; k<dc; k++)
                Rmn_SRL[i][j][k] = 0;

    for (var=0; var<it_max; var++)
        H_decoded[var] = 0;

    // Metrics    
    start_timer();	
    
    /* Loop through all decoding iterations */
    for (var=0; var<it_max; var++)
    {						
        /* Loop through all rows of parity check matrix */
        for (row=0; row<M_code; row++)
        {

            beta = 0; /* Inicializa el valor del sindrome a cero */
            /* Extract Qmn(a) messages from Qn(a) memories */
            for (i=0;i<dc;i++)
            {
                aux2 = pow_coefH[row][i] + 1;
                aux1 = q_field - aux2;

                /* PERMUTACION DE LA COLUMNA EXTRAIDA */
#ifdef VECTOR_EXT                
                asm volatile("addi	t0, zero, %0;" :: "I"(256));  // 64 (int64_t) * 32 (columns) / 8 
                asm volatile("vlse64.v v2, (%0), t0;" ::"r"(&Ln_aux[0][col[row][i]]));
                if (pow_coefH[row][i]!=0)
                {
                    // Clean vectors     
                    asm volatile("vmv.v.i v0, 0;");
                    asm volatile("vmv.v.i v4, 0;");
                    asm volatile("vmv.v.i v6, 0;");
                    asm volatile("vmv.v.i v8, 0;");
                    asm volatile("vmv.v.i v10, 0;");

                    // Permutation and clean position 0
                    asm volatile("vslidedown.vi v0, v2, 1;");
                    asm volatile("vslideup.vx v4, v0, %0;" :: "r"(aux2));                
                    asm volatile("vslidedown.vx v6, v2, %0;" :: "r"(aux1+1));
                    asm volatile("vslideup.vx v8, v6, %0;" :: "r"(1));   
                    asm volatile("vadd.vv v6, v4, v8;");

                    // Set position 0
                    asm volatile("vmv.v.x v8, %0;" :: "r"(Ln_aux[0][col[row][i]]));
                    asm volatile("vslidedown.vx v10, v8, %0;" :: "r"(q_field-1));

                    // Merge both vectors
                    asm volatile("vadd.vv v2, v6, v10;");
                }
                asm volatile("addi	t0, zero, %0;" :: "I"(32)); // 64 (int64_t) * 32 (columns) / 8 
                
                // Save Qmn in v2
                //asm volatile("vsse64.v v2, (%0), t0;" ::"r"(&Qmn[0][i]));   
#else

                for (j=0;j<q_field;j++)
                    Qmn_temp[j] = Ln_aux[j][col[row][i]];            


                if (pow_coefH[row][i]==0)
                {
                    for (j=0;j<q_field;j++)
                        Qmn[j][i] = Qmn_temp[j];                 
                }
                else
                {		                
                    for (k = aux2; k < q_field; k++)
                    {
                        Qmn[k][i] = Qmn_temp[k-aux2+1];
                    }
                    for (k = 1; k < aux2; k++)
                    {
                        Qmn[k][i] = Qmn_temp[k+aux1];
                    }
                    Qmn[0][i] = Qmn_temp[0];
                }
#endif                

                /***********************************/

                /* Qmn_prima = Qmn_p - reshape(Rmn_SRL(i,:,:),q_field,dc); */

                MAX_temp = 10000;
                for (j=0;j<q_field;j++)
                {
                    Qmn[j][i] = Qmn[j][i] - Rmn_SRL[row][j][i];

                    /* Busqueda del minimo para normalizacion */
                    if (Qmn[j][i] < MAX_temp) {
                        MAX_temp = Qmn[j][i];
                        z[i] = pos_exp_table[j];  
                    }
                }
                beta = gfadd[beta][z[i]];  /* SINDROME DEL CHECK NODE */

                /*****************************************/

                /* Normalizacion y precision finita*/
                for (j=0;j<q_field;j++)
                {
                    #if DECO_QUANT == 1
                    Qmn[j][i] = floor((Qmn[j][i]-MAX_temp)*QN_FLOORp1)*QN_FLOORm1; 
                        if(Qmn[j][i] > QN_SATp1)
                            Qmn[j][i] = QN_SATp1;
                    #else
                        Qmn[j][i] = Qmn[j][i]-MAX_temp; 
                    #endif
                }
                /*****************/
            }

            /*******************************************/
            /**********  CNU FUNCTION ******************/
            /*******************************************/
#ifdef FOR_BACK
            // Clean Forward and Backward variables and set value to first and last column
            // Clean R_Aux
            for(j=0;j<dc;j++){
                for(i=0;i<q_field;i++){        
                    if(j==0)
                        R_Forward[i][j] = Qmn[i][j];
                    else
                        R_Forward[i][j] = 0;

                    if(j==dc-1){
                        R_Backward[i][j] = Qmn[i][j];
                        Rmn[i][j] = Qmn[i][j];
                    }
                    else{
                        R_Backward[i][j] = 0;
                        Rmn[i][j] = 0;
                    }            
                }
            }

            for(a=2;a<dc;a++){
                for(i=0;i<q_field;i++){

                    min_temp = 10000;
                    min_temp_2 = 10000;     
                    min_temp_3 = 10000;           
                    for(k=0;k<q_field;k++){
                        // Search maximum
                        // Forward
                        if(R_Forward[k][a-2] > Qmn[wires[k][i]][a-1])
                            R_compare[k] = R_Forward[k][a-2];
                        else
                            R_compare[k] = Qmn[wires[k][i]][a-1];

                        // Backward
                        if(R_Backward[k][5-a] > Qmn[wires[k][i]][4-a])
                            R_compare_2[k] = R_Backward[k][5-a];
                        else
                            R_compare_2[k] = Qmn[wires[k][i]][4-a];

                        // Search minimum
                        // Forward
                        if(R_compare[k] < min_temp)
                            min_temp = R_compare[k];
                        // Backward
                        if(R_compare_2[k] < min_temp_2)
                            min_temp_2 = R_compare_2[k];

                        // Standard Min Max
                        // Search maximum
                        if(R_Forward[k][a-2] > R_Backward[wires[k][i]][a])
                                R_compare[k] = R_Forward[k][a-2];
                            else
                                R_compare[k] = R_Backward[wires[k][i]][a];
                        
                        // Search minimum
                        if(R_compare[k] < min_temp_3)
                            min_temp_3 = R_compare[k];
                    }
                    R_Forward[i][a-1] = min_temp;
                    R_Backward[i][4-a] = min_temp_2;
                    Rmn[i][a-1] = min_temp_3;
                }  
            }

            for(i=0;i<q_field;i++){
                Rmn[i][0] =       R_Backward[i][1];
                Rmn[i][dc-1] =    R_Forward[i][dc-2];
            }
#else                                                         
            /* paso de mensajes al dominio delta */
            for (i=0;i<dc;i++)
            {
                for (j=0;j<q_field;j++)
                {
                    temp[j][i] = gfadd[z[i]][pos_exp_table[j]];
                    dWmn[j][i] = Qmn[ exp_pos_table[ temp[j][i] ] -1][i];
                }
            }


            /* Busqueda de minimos */
            for (j=0;j<q_field;j++)
            {
                min_temp = dWmn[j][0];
                min_temp2 = 10000;
                pos_temp = 0;
            
                for (i=1;i<dc;i++)
                {
                    if (dWmn[j][i] < min_temp)
                    {
                        min_temp2 = min_temp;
                        min_temp = dWmn[j][i];
                        pos_temp = i;
                    }
                    else if (dWmn[j][i] < min_temp2)
                    {
                        min_temp2 = dWmn[j][i];
                    }
                }

                min1[j] = min_temp;
                min2[j] = min_temp2;
                pos[j] = pos_temp;
            }   

            /* Calculo de la columna extra */
            for (i=0;i<q_field-1;i++)
            {
                min_temp = min1[i+1];
                //float min2_temp = 10000;
                pos_temp = 0;
                
                max[0] = min1[i+1];
                for (j=0;j<q_field/2-1;j++)
                {
                    cam1_temp[j] = pos[conf_tb[j][0][i]-1];
                    cam2_temp[j] = pos[conf_tb[j][1][i]-1];
                    if (cam1_temp[j] == cam2_temp[j]) 
                    {
                        max[j+1] = 10000;
                    }
                    else
                    {
                        //max[j+1] = min1[conf_tb[j][0][i]-1] + min1[conf_tb[j][1][i]-1];
                        
                        if (min1[conf_tb[j][0][i]-1] > min1[conf_tb[j][1][i]-1])
                        {
                            max[j+1] = min1[conf_tb[j][0][i]-1];
                        }
                        else
                        {
                            max[j+1] = min1[conf_tb[j][1][i]-1];
                        }
                        
                    }
                    
                    if (max[j+1]<min_temp)
                    {
                        min_temp = max[j+1];
                        pos_temp = j+1;
                    }
                }
                
                min_global[i+1] = min_temp;
                
                if (pos_temp == 0)
                {
                    cam1[i+1] = pos[i+1];
                    cam2[i+1] = -1;
                }
                else
                {
                    cam1[i+1] = cam1_temp[pos_temp-1];
                    cam2[i+1] = cam2_temp[pos_temp-1];
                }
            }
                                        
            min_global[0] = 0;
            
            /* TEMPORAL PRINTF */
            /*
            printf("dQ = ");
            for (i = 0; i< q_field; i++)
                printf("%7.2f ",min_global[i]);
            printf("\n");*/
            
            
            /* Busqueda de los dos minimos valores en la columna extra */
            dQ_min1 = 10000;
            dQ_min2 = 10000;
            dQ_pos1 = 0;
            dQ_pos2 = 0;
            for (j=1;j<q_field;j++)
            {
                if (min_global[j] < dQ_min1)
                {
                    dQ_min2 = dQ_min1;
                    dQ_min1 = min_global[j];
                    dQ_pos2 = dQ_pos1;
                    dQ_pos1 = j;
                }
                else if (min_global[j] < dQ_min2)
                {
                    dQ_min2 = min_global[j];
                    dQ_pos2 = j;
                }
            }

            /*
            printf("dQ_min1 = %7.2f       pos = %d \n", dQ_min1,dQ_pos1);
            printf("dQ_min2 = %7.2f       pos = %d \n", dQ_min2,dQ_pos2);
            return;
            */
#endif            
            for (i=0;i<dc;i++)
            {				      
#ifndef FOR_BACK                          
                for (j=0;j<q_field;j++)
                {
                    if ( (j == dQ_pos1) || (j == dQ_pos2) || (j == 0) ) /* Si estamos en el elemento del campo que contiene el minimo de la columna extra entonces... */
                    {
                        if ((cam2[j] == -1)&&(i == cam1[j]))
                            oRmn_temp = min2[j];
                        else if ((i == cam1[j]) || (i == cam2[j]))
                            oRmn_temp = min1[j];
                        else
                            oRmn_temp = min_global[j];

                    }
                    else
                    {
                        //oRmn_temp = voto * MAX_temp2;
                        if ((cam2[j] == -1)&&(i == cam1[j]))
                            oRmn_temp = min2[j];
                        else if ((i == cam1[j]) || (i == cam2[j]))
                            oRmn_temp = min1[j];
                        else
                            oRmn_temp = dQ_min2;// voto * dQ_min2;
                    }
                    
                    temp[j][i] = exp_pos_table[gfadd[temp[j][i]][beta]]-1;
                    
                    /*Aplica escalado y precision finita a los mensajes de salida del CN*/
                    #if DECO_QUANT == 1						   
                        Rmn[temp[j][i]][i] = floor((oRmn_temp*scaling_factor)*CN_FLOORp1)*CN_FLOORm1; 
                            if(Rmn[temp[j][i]][i] > CN_SATp1)
                                Rmn[temp[j][i]][i] = CN_SATp1;
                    #else
                        Rmn[temp[j][i]][i] = oRmn_temp;//*scaling_factor;
                    #endif
                }
#endif
                for (j=0;j<q_field;j++)
                {
                
                    Rmn_SRL[row][j][i] = Rmn[j][i];

                    /*CNout = CNout + Qmn_prima;*/
                    Rmn[j][i] = Rmn[j][i] + Qmn[j][i];
                }

                /****** PERMUTACION INVERSA *******/
                aux1 = pow_coefH[row][i];
                aux2 = q_field - aux1;
#ifdef VECTOR_EXT               
                asm volatile("addi	t0, zero, %0;" :: "I"(32));  // 64 (int64_t) * 4 (columns) / 8 
                asm volatile("vlse64.v v2, (%0), t0;" ::"r"(&Rmn[0][i]));
                if (aux1!=0)
                {
                    // Clean vectors     
                    asm volatile("vmv.v.i v0, 0;");
                    asm volatile("vmv.v.i v4, 0;");
                    asm volatile("vmv.v.i v6, 0;");
                    asm volatile("vmv.v.i v8, 0;");
                    asm volatile("vmv.v.i v10, 0;");

                    // Permutation and clean position 0
                    asm volatile("vslidedown.vi v0, v2, 1;");
                    asm volatile("vslideup.vx v4, v0, %0;" :: "r"(aux2));                
                    asm volatile("vslidedown.vx v6, v2, %0;" :: "r"(aux1+1));
                    asm volatile("vslideup.vx v8, v6, %0;" :: "r"(1));   
                    asm volatile("vadd.vv v6, v4, v8;");

                    // Set position 0
                    asm volatile("vmv.v.x v8, %0;" :: "r"(Ln_aux[0][col[row][i]]));
                    asm volatile("vslidedown.vx v10, v8, %0;" :: "r"(q_field-1));

                    // Merge both vectors
                    asm volatile("vadd.vv v2, v6, v10;");
                }
                asm volatile("addi	t0, zero, %0;" :: "I"(32)); // 64 (int64_t) * 32 (columns) / 8 
                asm volatile("vsse64.v v2, (%0), t0;" ::"r"(&Qn_NEW[0][i]));   
#else 
                if (aux1==0) /* Si hmn es diferente de 0 o 1 entonces se permuta*/
                {
                    for (j=0;j<q_field;j++)
                    {
                        Qn_NEW[j][i] = Rmn[j][i];
                    }
                }
                else
                {
                    for (k = 1; k < q_field-aux1; k++)
                    {
                        Qn_NEW[k][i] = Rmn[aux1+k][i];
                    }
                    for (k = q_field-aux1; k < q_field; k++)
                    {
                        Qn_NEW[k][i] = Rmn[k-q_field+aux1+1][i];
                    }

                    Qn_NEW[0][i] = Rmn[0][i];
                }
#endif                
                /***********************************/

                /* PRECISION FINITA Y ACTUALIZACION DE LAS VN*/
//#ifdef VECTOR_EXT  
                //asm volatile("addi	t0, zero, %0;" :: "I"(256));  // 64 (int64_t) * 32 (columns) / 8 
                //asm volatile("vsse64.v v2, (%0), t0;" ::"r"(&Ln_aux[0][col[row][i]]));
//#else
                for (j=0;j<q_field;j++)
                {
                    #if DECO_QUANT == 1
                        Ln_aux[j][col[row][i]] = floor((Qn_NEW[j][i])*QN_FLOORp1)*QN_FLOORm1; 
                        if(Ln_aux[j][col[row][i]] > QN_SATp1)
                            Ln_aux[j][col[row][i]] = QN_SATp1;
                    #else
                        Ln_aux[j][col[row][i]] = Qn_NEW[j][i];
                    #endif
                }
//#endif
            }

            /******* TEMPORAL *************/
            
            /*for (i=0; i<dc; i++)
            {
                for (j=0; j<q_field; j++)
                {
                    printf("%7.4f ", Qn_NEW[j][i]);
                }
                printf("\n");
            }
            printf("\n");*/
            
            /******************************/

        }

        /*Tentatively decoding*/
        /*Compute: Qn(a)=Ln(a)+sum(Rmn)*/

        aux2 = 0;
        for (i=0;i<N_code;i++)
        {
            MAX_temp = 10000;
            for (j=0;j<q_field;j++)
            {
                /* Busqueda del minimo para normalizacion */
                if (Ln_aux[j][i] < MAX_temp)
                {
                    MAX_temp = Ln_aux[j][i];
                    aux1 = j;
                }
            }

            for (j=0;j<m_field;j++)
            {
                decoded[i][j] = fld_bpsk_bip[pos_exp_table[aux1]][j];
                if (decoded[i][j] != m[i][j])
                {
                    aux2 = aux2+1;
                }
            }
        }

        H_decoded[var] = aux2;

        if (aux2 == 0)
            break;

    }

    stop_timer();
    int64_t runtime = get_timer();

    printf("The execution took %d cycles.\n", runtime);

    for (i=0; i<it_max; i++)
    {
        MNBE_Hdecoded[i] = MNBE_Hdecoded[i] + H_decoded[i];
        MNPE_Hdecoded[i] = MNPE_Hdecoded[i] + (int)(H_decoded[i]>0);
    }

    printf("\n MNPE_Hdecoded = ");
    for (i=0; i<it_max; i++)
    {
        printf("%d ", MNPE_Hdecoded[i]);
    }
    printf("\n MNBE_Hdecoded = ");
    for (i=0; i<it_max; i++)
    {
        printf("%d ", MNBE_Hdecoded[i]);
    }
}