#include<stdio.h>
#include<stdlib.h>
#define NUM 5

void preencheMatriz(int nLinhas, int mat[nLinhas][3]){
    int i, j, existe;       /* -2b ... -2b (4 bytes) */
 

    for(i=0;i<nLinhas;i++){
        do{
            printf("Numero %d: ", i);
            scanf("%d", &mat[i][0]);
            existe = 0;

            for (j=0;j<i;j++){
                if(mat[j][0] == mat[i][0])
                    existe = 1;
            }
        }while (existe==1 || mat[i][0]<0 || mat[i][0]>100); /* =0 (FALSO) \ !0 (VERDADEIRO) */
        mat[i][1] = mat[i][0] = mat[i][0];  /* QUADRADO */       
        mat[i][2] = mat[i][1] = mat[i][0];  /* CUBO */
    }
    return;
}



int main(void){
    int n[NUM][3];

    preencheMatriz(NUM, n);
    return(0);

}