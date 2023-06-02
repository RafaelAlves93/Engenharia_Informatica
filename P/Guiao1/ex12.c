#include <stdio.h> // Exercicio no qual foi treinado ponteiros com matriz (exercicio correta mas talvez confuso) //

int verifica(int lmat1, int lmat2, int colmat1, int colmat2,char* mat1[][colmat1], char* mat2[][colmat2]);

int main(void) {

    int lmat1, colmat1; 
    int lmat2, colmat2;
    // primeira matriz
    printf("\n| | Matriz 1 | |\n");
    printf("Num de Linhas: ");
    scanf("%d", &lmat1);
    printf("Num de Colunas: ");
    scanf("%d", &colmat1);
    printf("\n");

    int mat1[lmat1][colmat1];

    for(int i = 0; i < lmat1; i++){
        for(int j = 0; j < colmat1; j++){
            printf("Valor da posicao [%d][%d]: ", i, j);
            scanf("%d", mat1[i]+j);
        }
    }
    // segunda matriz 
    printf("\n| | Matriz 2 | |\n");
    printf("Num de Linhas: ");
    scanf("%d", &lmat2);
    printf("Num de Colunas: ");
    scanf("%d", &colmat2);
    printf("\n");

    int mat2[lmat2][colmat2];

    for(int i = 0; i < lmat2; i++){
        for(int j = 0; j < colmat2; j++){
            printf("Valor da posicao [%d][%d]: ", i, j);
            scanf("%d", mat2[i]+j);
        }
    }

    // chamada da função
    if(verifica(lmat1, lmat2, colmat1, colmat2, mat1, mat2))
        printf("\nAs matrizes SAO iguais\n");
    else printf("\nAs matrizes NAO sao iguais\n");
    for(int* p = *mat1; p <= *(mat1+colmat1-1)+lmat1-1; p++)
        printf("%d ",*p);
    printf("\n");
    for(int* p = *mat2; p <= *(mat2+colmat2-1)+lmat2-1; p++)
        printf("%d ", *p);
}

int verifica(int lmat1, int lmat2, int colmat1, int colmat2, char* mat1[][colmat1], char* mat2[][colmat2]) {
 	if(colmat1 != colmat2 || lmat1 != lmat2) return 0;
 	int cont = 0;
    for(int i = 0; i < lmat1; i++)
        for(int j = 0; j < lmat1; j++)
            cont += *(mat1[i]+j) == *(mat2[i]+j);
 	if(cont) return 1;
    return 0;
 }