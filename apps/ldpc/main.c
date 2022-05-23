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

float Ln_aux[16][32] = {
    {3.459869,1.087765,3.810277,0.033718,2.734296,0.480646,1.598187,1.444215,5.502400,2.407383,0.323405,0.589172,3.055819,2.791696,1.805277,2.318196,3.044381,3.511888,4.523205,0.995117,2.900628,6.480545,1.371912,0.849076,6.187487,1.872699,1.588403,1.383852,1.075101,2.476810,2.486768,2.593169},
    {0.180465,0.220250,4.817748,0.000000,2.005587,1.177546,3.184414,1.586673,3.798960,3.953394,1.644678,2.528416,1.320958,1.185444,3.395372,3.151575,2.522050,3.116177,3.058877,0.406078,1.938680,4.804595,1.632628,1.803535,4.323974,0.325429,2.042378,3.484864,3.006039,1.160262,4.243139,0.800769},
    {4.823557,0.867514,2.035961,1.679835,1.745345,0.000000,0.012586,2.497433,3.106027,1.310691,1.128600,1.599102,2.573309,4.411648,2.158646,0.000000,5.483795,2.108374,2.715367,2.282487,2.057518,4.934940,0.623486,0.000000,4.279983,2.008838,2.651392,2.824087,0.707755,1.316548,1.681487,2.307439},
    {4.240382,1.377377,2.601220,0.314844,4.727311,1.644096,1.585601,1.105088,4.541768,1.406615,0.853489,1.469638,2.217370,4.325317,1.398745,3.766518,1.918771,3.129233,3.272166,2.545881,3.785570,4.254640,1.123564,2.333643,6.577834,1.547270,0.699148,0.000000,3.044011,3.569757,2.018105,4.559467},
    {3.279404,3.236444,2.983373,0.386291,1.717660,1.890992,3.078129,0.339127,5.060444,2.097461,0.000000,0.000000,4.142158,1.606252,0.406532,3.806338,1.647941,2.181879,5.120295,0.589039,1.805057,5.447459,0.996774,1.229568,3.771017,4.470149,0.889255,3.431535,0.367346,3.419679,1.273944,2.078131},
    {1.544153,0.000000,3.043432,1.646117,1.016635,0.696900,1.598814,2.639891,1.402587,2.856702,2.449873,3.538346,0.838449,2.805396,3.748742,0.833378,4.961464,1.712663,1.251039,1.693447,1.095571,3.258991,0.884202,0.954459,2.416470,0.461567,3.105367,4.925100,2.638693,0.000000,3.437859,0.515038},
    {5.604070,1.157127,0.826904,1.960962,3.738360,1.163449,0.000000,2.158306,2.145396,0.309922,1.658685,2.479568,1.734860,5.945269,1.752114,1.448322,4.358185,1.725719,1.464328,3.833250,2.942461,2.709035,0.375138,1.484567,4.670330,1.683409,1.762138,1.440236,2.676665,2.409496,1.212824,4.273736},
    {4.059917,3.526056,1.774316,0.667418,3.710676,3.054441,3.065543,0.000000,4.099812,1.096693,0.530085,0.880466,3.303710,3.139873,0.000000,5.254659,0.522331,1.799224,3.869256,2.139803,2.690000,3.221554,0.748426,2.714135,4.161364,4.144721,0.000000,2.047684,2.336256,4.512626,0.805281,4.044429},
    {1.363688,2.148679,2.216528,1.998691,0.000000,2.107245,3.078755,1.534803,0.960631,2.546780,2.126468,2.949175,1.924788,1.619952,2.349997,2.321519,3.565024,0.382654,1.848128,1.287369,0.000000,2.225905,0.509064,1.334951,0.000000,3.059018,2.406219,6.972784,1.930938,0.942868,2.225034,0.000000},
    {0.960978,0.509863,3.608691,0.281127,3.998602,2.340996,3.171828,1.247546,2.838328,2.952626,2.174762,3.408883,0.482510,2.719065,2.988840,4.599896,1.396440,2.733523,1.807838,1.956841,2.823623,2.578691,1.384280,3.288102,4.714321,0.000000,1.153123,2.101013,4.974949,2.253209,3.774477,2.767066},
    {4.643092,3.016193,1.209057,2.032409,0.728709,1.410345,1.492528,1.392344,2.664072,1.000769,0.805195,1.009930,3.659649,3.226204,0.759902,1.488141,4.087355,0.778365,3.312457,1.876408,0.961947,3.901854,0.248348,0.380492,1.863513,4.606288,1.952244,4.871771,0.000000,2.259417,0.468663,1.792400},
    {2.324666,0.289613,1.834375,1.927244,3.009651,1.860349,1.586227,2.300764,0.441956,1.855933,2.979958,4.418813,0.000000,4.339017,3.342209,2.281700,3.835854,1.330009,0.000000,3.244211,1.980513,1.033086,0.635854,2.439025,2.806817,0.136139,2.216113,3.541248,4.607603,1.092947,2.969196,2.481335},
    {5.423605,3.305806,0.000000,2.313535,2.721724,2.573795,1.479942,1.053217,1.703440,0.000000,1.335280,1.890397,2.821200,4.759825,0.353369,2.936463,2.961745,0.395710,2.061418,3.427172,1.846890,1.675950,0.000000,1.865059,2.253860,4.280860,1.062989,3.487919,1.968910,3.352364,0.000000,3.758698},
    {2.144201,2.438292,1.007471,2.279818,1.993015,3.270695,3.066169,1.195675,0.000000,1.546011,2.656553,3.829641,1.086340,3.153573,1.943465,3.769841,2.439414,0.000000,0.597089,2.838132,0.884943,0.000000,0.260716,2.819518,0.390347,2.733589,1.516964,5.588932,3.899848,2.035816,1.756372,1.966297},
    {0.780513,2.658542,2.781787,0.633700,2.981966,3.751341,4.651770,0.142458,2.396372,2.642704,1.851358,2.819711,1.568849,1.533621,1.590095,6.088038,0.000000,1.403514,2.404927,1.550763,1.728052,1.545605,1.009142,3.668594,2.297851,2.597450,0.453975,4.148696,4.267194,3.196077,2.561653,2.252028},
    {0.000000,2.368929,3.990844,0.352574,0.988951,2.587892,4.664356,0.481585,3.357004,3.643473,1.321273,1.939245,2.407298,0.000000,1.996628,4.639716,1.125610,1.786168,3.655966,0.000000,0.843109,3.771509,1.257490,2.184027,1.907504,2.922879,1.343230,5.532548,2.298284,2.103130,3.030315,0.285731}
};

int main(void)
{   
    int i,j,k,var,row; /* Used for loop indexs */

    //float SNRdB[10];
    //float sigma[10];
    //float sigma_2[10];

    int 	decoded[N_code][m_field];
    //float 	r_ch[N_code][m_field];
    //float 	Ln_aux[q_field][N_code];
    float 	Rmn_SRL[M_code][q_field][dc];

    float Qmn[q_field][dc];
    float Qmn_temp[q_field];

    int aux1, aux2;
    float MAX_temp; //MAX_temp2;

    float dQ_min1, dQ_min2; 
    int dQ_pos1, dQ_pos2;

    int beta;
    int z[dc];
    float dWmn[q_field][dc];
    int temp[q_field][dc];
    float min1[q_field], min2[q_field];
    int pos[q_field];
    float max[q_field/2];
    int cam1_temp[q_field/2 - 1], cam2_temp[q_field/2 - 1];
    float min_global[q_field]; //min2_global[q_field];
    int cam1[q_field], cam2[q_field];
    float Rmn[q_field][dc];
    float Qn_NEW[q_field][dc];

    int H_decoded[it_max];
    int MNBE_Hdecoded[it_max];
    int MNPE_Hdecoded[it_max];

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
        //printf("Iteracion %d\n",var);
        printf("iter: %d\n", var);
        /* Loop through all rows of parity check matrix */        
        for (row=0; row<M_code; row++)
        {

            beta = 0; /* Inicializa el valor del sindrome a cero */
            /* Extract Qmn(a) messages from Qn(a) memories */
            for (i=0;i<dc;i++)
            {

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
                    aux2 = pow_coefH[row][i] + 1;
                    aux1 = q_field - aux2;

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
                float min_temp = dWmn[j][0];
                float min_temp2 = 10000;
                int pos_temp = 0;
            
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
                float min_temp = min1[i+1];
                //float min2_temp = 10000;
                int pos_temp = 0;
                
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
                float oRmn_temp;
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
                            oRmn_temp = dQ_min2;//voto * dQ_min2;
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