#include <stdint.h>
#include <string.h>

#include "printf.h"
#include "runtime.h"
#include "Hmat_N32_M16_GF16.h"

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


int main() {
    printf("\n");
    printf("=============\n");
    printf("=  RISC-V V =\n");
    printf("=============\n");
    printf("\n");
    printf("\n");

    int64_t Qmn_temp[q_field];
    int64_t Qmn[q_field][dc], Qmn2[q_field][dc], Qn_NEW[q_field][dc], Qn_NEW2[q_field][dc];
    int64_t runtime = 0, base = 0, vec = 0;
    int64_t aux1, aux2;



    unsigned long int block_size_p;
    // Set the vector configuration
    asm volatile("vsetvli %0, %1, e64, m1, ta, ma" : "=r"(block_size_p) : "r"(q_field));
    printf("Block size: %d\n", block_size_p);

    int row, i, j, k;
    int error = 0;
    for (row=0; row<M_code; row++)
    {
        /* Extract Qmn(a) messages from Qn(a) memories */
        for (i=0;i<dc;i++)
        {
            //if(i==1)
            //    return 0;
            //aux2 = pow_coefH[row][i] + 1;
            //aux1 = q_field - aux2;

            // Instrucciones Base
            start_timer();

            for (j=0;j<q_field;j++)
                Qmn_temp[j] = Ln_aux[j][col[row][i]]; 
            
            /*if (pow_coefH[row][i]==0)
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
            }*/

            aux1 = pow_coefH[row][i];
            aux2 = q_field - aux1;
            if (aux1==0) /* Si hmn es diferente de 0 o 1 entonces se permuta*/
            {
                for (j=0;j<q_field;j++)
                {
                    Qn_NEW[j][i] = Qmn_temp[j];
                }
            }
            else
            {
                for (k = 1; k < q_field-aux1; k++)
                {
                    Qn_NEW[k][i] = Qmn_temp[aux1+k];
                }
                for (k = q_field-aux1; k < q_field; k++)
                {
                    Qn_NEW[k][i] = Qmn_temp[k-q_field+aux1+1];
                }

                Qn_NEW[0][i] = Qmn_temp[0];
            }
            stop_timer();
            runtime = get_timer();
            printf("Base instruction set took %d cycles.\n", runtime);
            base += runtime;

            // Vector
            start_timer(); 
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
            asm volatile("vsse64.v v2, (%0), t0;" ::"r"(&Qn_NEW2[0][i]));   
            stop_timer();
            runtime = get_timer();
            printf("Vector extension took %d cycles.\n", runtime);
            vec += runtime;        

            printf("H: %d\n",pow_coefH[row][i]);
            printf("aux1: %d\n",aux1);
            //printf("aux2: %d\n",aux2);
            for (j=0;j<q_field;j++)
            {
               
                if(Qn_NEW[j][i]!=Qn_NEW2[j][i])
                    error = 1;
                //printf("%d\t%d\t%d\n",Qmn_temp[j],Qn_NEW[j][i], Qn_NEW2[j][i]);
            }   
            printf("[row] = %d, [i] = %d, Error = %d\n",row,i,error);
        }        
    }    
    printf("--------------------------------------\n");
    printf("--------------------------------------\n");
    printf("Base instruction set: \t%d cycles.\n", base);
    printf("Vector extension: \t%d cycles.\n", vec);
    printf("--------------------------------------\n");
    printf("--------------------------------------\n");         

  return 0;
}
