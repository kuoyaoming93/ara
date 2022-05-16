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

//#include "input.h"

int Ln_aux[16][32] = {
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

int main(void)
{   
    int i,j,k,var,row; /* Used for loop indexs */

    //float SNRdB[10];
    //float sigma[10];
    //float sigma_2[10];

    int64_t 	decoded[N_code][m_field];
    //float 	r_ch[N_code][m_field];
    //float 	Ln_aux[q_field][N_code];
    int64_t 	Rmn_SRL[M_code][q_field][dc];

    int64_t Qmn[q_field][dc];
    int64_t Qmn_temp[q_field];

    int64_t aux1, aux2;
    int64_t MAX_temp; //MAX_temp2;

    int64_t dQ_min1, dQ_min2; 
    int64_t dQ_pos1, dQ_pos2;

    int64_t beta;
    int64_t z[dc];
    int64_t dWmn[q_field][dc];
    int64_t temp[q_field][dc];
    int64_t min1[q_field], min2[q_field];
    int64_t pos[q_field];
    int64_t max[q_field/2];
    int64_t cam1_temp[q_field/2 - 1], cam2_temp[q_field/2 - 1];
    int64_t min_global[q_field]; //min2_global[q_field];
    int64_t cam1[q_field], cam2[q_field];
    int64_t Rmn[q_field][dc];
    int64_t Qn_NEW[q_field][dc];

    int64_t H_decoded[it_max];
    int MNBE_Hdecoded[it_max];
    int MNPE_Hdecoded[it_max];

    int64_t min_temp;
	int64_t min_temp2;
	int64_t pos_temp;

	int64_t oRmn_temp;

    //int error = 0;

    /*printf("LLR Function: ");
    for (i = 0; i< q_field; i++){
        for(j=0; j<N_code;j++)
            printf("%f, \n",Ln_aux[i][j]);
        printf("\n");
    }*/

    printf("Hola! \n");

    /* Inicialize Rmn_SRL to zero values */
    for (i = 0; i<M_code; i++)
        for (j=0; j<q_field; j++)
            for (k=0; k<dc; k++)
                Rmn_SRL[i][j][k] = 0.0;

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

                for (j=0;j<q_field;j++)
                {
                    Qmn_temp[j] = Ln_aux[j][col[row][i]];
                }

                /* PERMUTACION DE LA COLUMNA EXTRAIDA */

                if (pow_coefH[row][i]==0)
                {
                    for (j=0;j<q_field;j++)
                    {
                        Qmn[j][i] = Qmn_temp[j];
                    }
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
            
            for (i=0;i<dc;i++)
            {				                
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

                for (j=0;j<q_field;j++)
                {
                
                    Rmn_SRL[row][j][i] = Rmn[j][i];

                    /*CNout = CNout + Qmn_prima;*/
                    Rmn[j][i] = Rmn[j][i] + Qmn[j][i];
                }

                /****** PERMUTACION INVERSA *******/
                aux1 = pow_coefH[row][i];
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
                /***********************************/

                /* PRECISION FINITA Y ACTUALIZACION DE LAS VN*/

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