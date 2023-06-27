// RAFAEL FILIPE MARTINS ALVES - 2014013189

#include "paragem.h"


int printaTitulos(char* nomeF) {
    FILE* f = fopen(nomeF, "r");
    if(f == NULL) return 0;

    char linha[200];

    while(fgets(linha, 200, f) != NULL)
        printf("%s", linha);
    fclose(f);
    return 1;
}

void registar_paragem(int *num_paragens, Paragem** paragens) {
    srand(time(NULL));
    int num_digitos = 0;
    Paragem nova_paragem;

    printf("\n\t================");
    printf("\n\tRegistar Paragem\n");
    printf("\t================\n");
    printf("\tNome: ");
    scanf(" %[^\n]", nova_paragem.nome);

    //Verifica se já existe uma paragem com o mesmo nome no array de paragens
    for (int i = 0; i < *num_paragens; i++) {
        if (strcmp((*paragens + i)->nome, nova_paragem.nome) == 0) {        //Compara o nome da nova paragem com o nome de cada paragem existente
            printf("\n\tJa existe uma paragem com o mesmo nome!\n\n");
            return;
        }
    }

    while (num_digitos == 0){
        //Gera um código alfanumérico de 4 caracteres
        for (int i = 0; i < 4; i++) {
            int random_char = rand() % 36;
            if (random_char < 26) {
                //Gera uma letra maiúscula
                nova_paragem.codigo[i] = 'A' + random_char;
            } else {
                //Gera um dígito
                nova_paragem.codigo[i] = '0' + random_char - 26;
                num_digitos++;
            }
        }
    nova_paragem.codigo[4] = '\0';          //\0 garante que seja tratado como uma string
    }

    //Percorre o array de paragens existentes e compara o codigo da nova paragem com o codigo de cada paragem existente
    for (int i = 0; i < *num_paragens; i++) {
        if (strcmp((*paragens + i)->codigo, nova_paragem.codigo) == 0) {
            printf("\n\tJa existe uma paragem com o mesmo codigo!\n");
            return;
        }
    }

    //Adiciona a nova paragem ao array de paragens
    (*num_paragens)++;
    *paragens = (Paragem*) realloc(*paragens, ((*num_paragens) * sizeof(Paragem)));
    if(*paragens == NULL) {
        printf("Erro: falha ao alocar memória para a nova paragem.\n");
        (*num_paragens)--;  //Reverte a contagem de paragens
        return;
    }
    int indice = ((*num_paragens)-1);           //Obtem o indice da nova paragem no array de paragens
    //strcpy((*paragens+indice)->nome , nova_paragem.nome);
    //strcpy((*paragens+indice)->codigo , nova_paragem.codigo);
    memcpy((*paragens + indice), &nova_paragem, sizeof(struct Paragem));    //Copia as informacoes da nova paragem para a posicao correta no array
    printf("\n\tParagem registada com sucesso!\n");
    printf("\tNome: %s\n", (*paragens+indice)->nome);
    printf("\tCodigo: %s\n\n", (*paragens+indice)->codigo);
}

void visualizar_paragens(int *num_paragens, Paragem** paragens) {
    printf("\n\t===================");
    printf("\n\tParagens Registadas\n");
    printf("\t===================\n");

    if(*num_paragens == 0) {
        printf("\n\tNenhuma paragem registada!!\n\n");
        return;
    }

    printf("\n\t--------------------------------------\n");
    printf("\t%s \t\t%s\n", "Codigo", "Nome");
    printf("\t--------------------------------------\n");

    for(int i = 0; i < (*num_paragens); i++) {
        printf("\t%s \t\t%s\n", (*paragens+i)->codigo, (*paragens+i)->nome);
    }
    printf("\n");
}

void eliminar_paragem(int *num_paragens, Paragem** paragens, char codigo[5]) {//IMCOMPLETO!! FALTA VERIFICAR SE A PARAGEM PERTENCE A UMA LISTA
    int i;

    if(strcmp(codigo, "sair") == 0){
        printf("\n");
        return;
    }

    printf("\n\t=================\n");
    printf("\tEliminar Paragem\n");
    printf("\t=================\n");

    //Verificar se há paragens registadas
    if (*num_paragens == 0) {
        printf("\tNao ha paragens registadas!\n\n");
        return;
    }

    //Procurar e apagar a paragem com o código inserido
    for(i=0; i <= (*num_paragens); i++) {
        if(strcmp((*paragens+i)->codigo, codigo) == 0) {       //Compara o codigo da paragem atual com o código do scanf
            for(int j=i; j < (*num_paragens - 1); j++) {     //Se encontrar uma paragem com o mesmo código, remove a paragem movendo todas as paragens seguintes uma posição para tras no array.
                (*paragens)[j] = (*paragens)[j + 1];
                //strcpy((*paragens + i)->nome, (*paragens + i + 1)->nome);
                //strcpy((*paragens + i)->codigo, (*paragens + i + 1)->codigo);
            }
            (*num_paragens)--;
            *paragens = (Paragem*) realloc(*paragens, *num_paragens * sizeof(Paragem)); //realloc para colocar tudo ok
            printf("\n\tParagem com o codigo %s foi removida!\n\n", codigo);
            break;
        }
    }
    if (i > *num_paragens) {              //Se o i for >= de num_paragens ja percorreu o array e nao encontrou
        printf("\tNao foi encontrada nenhuma paragem com o codigo %s!\n\n", codigo);
        fflush(stdin);
    }
}

void freeParagem(Paragem** paragens) {
    if (paragens == NULL) {
        return;
    }
    free(*paragens);
}


