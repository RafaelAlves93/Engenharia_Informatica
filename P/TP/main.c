// RAFAEL FILIPE MARTINS ALVES - 2014013189

#include "paragem.h"
#include "linha.h"


int main() {
    //srand(time(NULL));

    //Variáveis globais
    Paragem *paragens = NULL;       //Estrutura do array dinamico
    Linha *linhas = NULL;           //Estrutura do array dinamico
    int num_paragens = 0;
    int num_linhas = 0;

    int opcao, titulo;
    char cod[10], nometxt[50];

    titulo = printaTitulos("../Titulos/titulo.txt");
    printf("\n");
    if(!titulo){
        printf("\n\t\t\tO ficheiro de texto do titulo nao existe\n");
    }

    //Verificar se o arquivo binário existe
    FILE *f1 = fopen("../paragens.bin", "rb");
    if (f1 == NULL) {
        printf("\n\t-> Bem-Vindo, por ser a primeira vez a usar o Metro Mondego ainda nao existe ficheiro binario das paragens!\n");
    } else {
        fclose(f1);
        loadBinParagens(&num_paragens, &paragens);
        loadBinLinhas(&num_linhas, &linhas);
    }
    /*
    FILE *f2 = fopen("../linhas.bin", "rb");
    if (f1 == NULL) {
        printf("\t-> Bem-Vindo, por ser a primeira vez a usar o Metro Mondego ainda nao existe ficheiro binario das linhas!\n\n");
    } else {
        fclose(f2);
        //Carrega os dados armazenados
        //loadBin(&num_paragens, &paragens, &num_linhas, &linhas);
    }*/

    do {
        printf("\n\n\t--------------------------\n");
        printf("\t| 1. Registar Paragem    |\n");
        printf("\t| 2. Eliminar Paragem    |\n");
        printf("\t| 3. Visualizar Paragens |\n");
        printf("\t| 4. Adicionar Linha     |\n");
        printf("\t| 5. Atualizar Linha     |\n");
        printf("\t| 6. Visualizar Linhas   |\n");
        printf("\t| 7. Listar Percursos    |\n");
        printf("\t| 8. Carregar Dados txt  |\n");
        printf("\t| 0. Sair                |\n");
        printf("\t--------------------------\n");
        printf("\tOpcao: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch(opcao) {
            case 1:
                registar_paragem(&num_paragens, &paragens);
                break;
            case 2:
                while(1){
                    printf("\n\tInsira o codigo da paragem a eliminar ou digite 'sair' para parar: ");
                    scanf(" %4s", cod);
                    if (strcmp(cod, "sair") == 0) {
                        break;
                    }
                    if (strlen(cod) != 4) {
                        printf("\tTem de inserir um codigo com 4 caracteres alfanumericos!\n\n");
                    }
                    else{
                        break;
                    }
                }
                int verify=verificaPLinha(&num_linhas, &linhas, cod);

                if(verify==0){
                    eliminar_paragem(&num_paragens, &paragens, cod);
                }
                break;
            case 3:
                visualizar_paragens(&num_paragens, &paragens);
                break;
            case 4:
                if(num_paragens>0){
                    regista_linha(&num_paragens, &num_linhas, &linhas, &paragens);
                }
                else{
                    printf("\tNao existem paragem registadas!\n\n");
                }
                break;
            case 5:
                atualizar_linha(& num_linhas, &linhas, &paragens, &num_paragens);
                break;
            case 6:
                visualizar_linhas(&num_linhas, &linhas);
                break;
            case 7:
                if (num_linhas == 0){
                    printf("\n\tTem de ter pelo menos uma linha criada!\n");
                }
                else{
                    printf("\n\tNome da paragem inicial: ");
                    char nparageminicial[50];
                    scanf(" %[^\n]", nparageminicial);
                    fflush(stdin);
                    printf("\n\tNome da paragem final: ");
                    char nparagemfinal[50];
                    scanf(" %[^\n]", nparagemfinal);
                    fflush(stdin);
                    Paragem* paragemInicial = NULL;
                    Paragem* paragemFinal = NULL;
                    for (int i = 0; i < num_paragens; i++) {
                        if(strcmp((paragens+i)->nome, nparageminicial) == 0 ){
                            paragemInicial = (paragens+i);
                        }
                        if(strcmp((paragens+i)->nome, nparagemfinal) == 0 ){
                            paragemFinal = (paragens+i);
                        }
                    }
                    if (paragemInicial == NULL){
                        printf("\n\tParagem inicial %s nao existe", nparageminicial);
                        break;
                    }
                    else if(paragemFinal == NULL){
                        printf("\n\tParagem final %s nao existe", nparagemfinal);
                        break;
                    }
                    else{
                        calcPercurso(paragemInicial, paragemFinal, &num_linhas, &linhas);
                        break;
                    }
                }
            case 8:
                printf("\n\tInsira o nome do ficheiro: ");
                scanf(" %[^\n]", nometxt);
                leDadostxt(nometxt, &linhas, &paragens, &num_paragens, &num_linhas);
                break;
            case 0:
                printf("\n\tA terminar...\n");
                saveBinParagens(&num_paragens, &paragens);
                saveBinLinhas(&num_linhas, &linhas);
                freeLinha(&linhas);
                freeParagem(&paragens);
                break;
            default:
                printf("\n\tOpcao invalida!!\n\n");
                break;
        }
    } while(opcao != 0);
    return 0;
}