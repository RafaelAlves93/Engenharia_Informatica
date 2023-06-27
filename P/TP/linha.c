// RAFAEL FILIPE MARTINS ALVES - 2014013189

#include "linha.h"

Linha_Paragem* adicionar_linhaParagem(Paragem paragem) {       
    Linha_Paragem* no = (Linha_Paragem*)malloc(sizeof(Linha_Paragem));
    //printf("\n%s", (paragem)->codigo);
    no->paragem = paragem;
    //memcpy((&no->paragem), &paragem, sizeof(Paragem));
    //strcpy(no->paragem.nome , paragem.nome);
    //strcpy(no->paragem.codigo , paragem.codigo);
    no->prox = NULL;
    no->ant = NULL;
    return no;
}

void inserirLinhaParagem(Linha* linha, Paragem* paragem) {
    Linha_Paragem* no = adicionar_linhaParagem(*paragem);
    //printf("\n%s", (paragem)->codigo);
    if (linha->head == NULL) {
        linha->head = no;
    } else {
        Linha_Paragem* curr = (*linha).head;
        while (curr->prox != NULL) {
            curr = curr->prox;
        }
        curr->prox = no;
        no->ant = curr;
    }
}

void regista_linha(int *num_paragens, int *num_linhas, Linha** linhas, Paragem** paragens){
    char nomeP[50];

    (*num_linhas)++;
    *linhas = (Linha *) realloc(*linhas, ((*num_linhas) * sizeof(Linha)));

    int numL=(*num_linhas)-1;

    printf("\n\t================");
    printf("\n\tRegistar Linha\n");
    printf("\t================\n");
    printf("\tNome: ");
    //scanf(" %[^\n]", (*linhas)->nome);
    scanf(" %[^\n]", ((*linhas)+numL)->nome);
    ((*linhas)+numL)->head = NULL;
    fflush(stdin);

    // Verificar se já existe uma linha com o mesmo nome
    for (int i = 0; i < (*num_linhas) - 1; i++) {
        if (strcmp((*linhas + i)->nome, nomeP) == 0) {
            printf("\n\tJa existe uma linha com o mesmo nome!\n");
            (*num_linhas)--;
            return;
        }
    }

    while (1) {
        printf("\n");
        printf("\tInsira o nome da Paragem ou digite 'sair' para parar: ");
        //fgets(nomeP, sizeof(nomeP), stdin);
        scanf(" %[^\n]", nomeP);
        //nomeP[strcspn(nomeP, "\n")] = '\0'; // Remove trailing newline character

        if (strcmp(nomeP, "sair") == 0) {
            if (((*linhas) + numL)->head != NULL) {
                printf("\n");
                break;
            } else {
                printf("\tNao pode sair sem a criacao de uma paragem!\n");
                continue;
            }
        }

        Paragem* Pcorres = NULL;                //Verifica se a paragem ja existe
        for (int i = 0; i < (*num_paragens); i++) {
            if (strcmp((*paragens + i)->nome, nomeP) == 0) {
                Pcorres = (*paragens + i);
                break;
            }
        }

        if (Pcorres == NULL) {
            printf("\tNao existe nenhuma paragem com esse nome!\n");
            continue;
        }

        Linha_Paragem* curr = ((*linhas) + numL)->head;
        while (curr != NULL) {
            if (strcmp(curr->paragem.codigo, Pcorres->codigo) == 0) {
                printf("\tA paragem ja foi adicionada!\n");
                Pcorres = NULL;
                break;
            }
            curr = curr->prox;
        }

        if (Pcorres != NULL) {
            inserirLinhaParagem(((*linhas) + numL), Pcorres);
            printf("\n\tParagem adicionada com sucesso!\n");
        }
    }
}

void visualizar_linhas(int *num_linhas, Linha** linhas) {
    printf("\n\t=================");
    printf("\n\tLinhas Registadas\n");
    printf("\t=================\n\n");

    if(*num_linhas == 0) {
        printf("\tNenhuma linha registada!!\n\n");
        return;
    }
    for(int i = 0; i < (*num_linhas); i++) {
        printf("\tLinha: %s", (*linhas + i)->nome);
        //printf("\tLinha: \n");
        //printf("\t%s", (*linhas + i)->nome);
        //printf("%s", (*linhas + i)->head->paragem->codigo);
        printf("\n\t--------------------------------------\n");
        printf("\t%s \t\t%s\n", "Codigo", "Nome");
        printf("\t--------------------------------------\n");

        Linha_Paragem *curr = (*linhas + i)->head;

        while (curr != NULL) {
            printf("\t%s \t\t%s\n", curr->paragem.codigo, curr->paragem.nome);
            curr = curr->prox;
        }
        printf("\n");
    }
}

void saveBinParagens(int *num_paragens, Paragem** paragens){
    FILE *f;
    f = fopen("../paragens.bin", "wb");
    if(f == NULL){
        printf("\n\tErro ao criar o ficheiro paragens!!\n");
        return;
    }
    fwrite(*paragens, sizeof(Paragem), *num_paragens, f);
    //fwrite(*linhas, sizeof(Linha), *num_linhas, f);
    fclose(f);
}

void saveBinLinhas(int *num_linhas, Linha** linhas){
    FILE *f;
    f = fopen("../linhas.bin", "wb");
    if (f == NULL) {
        printf("\n\tErro ao criar o ficheiro linhas!!.\n");
        return;
    }
    //fwrite(*linhas, sizeof(struct Linha), *numLinhas, arquivo);
    fwrite(num_linhas, sizeof(int), 1, f);

    for (int i = 0; i < *num_linhas; i++) {
        Linha linha = (*linhas)[i];
        fwrite(&linha, sizeof(Linha), 1, f);

        Linha_Paragem* cont = linha.head;
        int contador=0;
        while (cont != NULL) {
            contador++;
            cont = cont->prox;
        }
        fwrite(&contador, sizeof(int), 1, f);
        Linha_Paragem* curr = linha.head;
        while (curr != NULL) {
            fwrite(&(curr->paragem), sizeof(Paragem), 1, f);
            curr = curr->prox;
        }
    }
    fclose(f);
}

void loadBinParagens(int *num_paragens, Paragem** paragens){
    FILE *f;
    f = fopen("../paragens.bin", "rb");
    if (f == NULL) {
        printf("\n\tFicheiro paragens nao encontrado!!\n");
        return;
    }
    //Obter o tamanho do ficheiro
    fseek(f, 0, SEEK_END);                                      //Posiciona o ponteiro do ficheiro no final
    long fileSize = ftell(f);                                   //Obtém a posição atual do ponteiro, que representa o tamanho do ficheiro (fileSize contem o tamanho).
    rewind(f);                                                  //Reposiciona o ponteiro do ficheiro no início

    //Calcular o número de elementos no array
    int size = fileSize / sizeof(Paragem);

    //Alocar memória para o array
    *paragens = (Paragem*) malloc(fileSize);
    if (*paragens == NULL) {
        printf("\tErro ao alocar memoria!\n");
        fclose(f);
    }
    //Ler ficheiro para array
    *num_paragens = fread(*paragens, sizeof(Paragem), size, f);
    printf("\n");
    if(*num_paragens != size ){
        printf("\tErro ao ler o ficheiro!\n\n");
        fclose(f);
    }
    fclose(f);
}

void loadBinLinhas(int *num_linhas, Linha** linhas){
    FILE *f;
    f = fopen("../linhas.bin", "rb");
    if (f == NULL) {
        printf("\n\tFicheiro linhas nao encontrado!!\n");
        return;
    }

    fread(num_linhas, sizeof(int), 1, f);
    *linhas = (Linha *) realloc(*linhas, *num_linhas * sizeof(Linha));


    for (int i = 0; i < *num_linhas; i++) {
        fread((*linhas+i), sizeof(Linha), 1, f);
        int contador;
        fread(&contador, sizeof(int), 1, f);
        (*linhas+i)->head = NULL;           //Definir o ponteiro head como NULL para cada linha
        //printf("\nLinha: %s contador: %d", (*linhas+i)->nome, contador);
        for (int j = 0; j < contador; j++) {
            Paragem *aux = (Paragem*) malloc(sizeof(Paragem));
            fread(aux, sizeof(Paragem), 1, f);
            //printf("\nparagem: %s", aux->nome);
            inserirLinhaParagem((*linhas+i),aux);
        }
    }
    fclose(f);
}

char* cortaespaco(char* str) {
    //Apagar à esquerda
    char* inicio = str;
    while (isspace(*inicio)) {
        inicio++;
    }
    //Apagar à direita
    char* fim = inicio + strlen(inicio) - 1;
    while (fim > inicio && isspace(*fim)) {
        fim--;
    }
    *(fim + 1) = '\0';
    return inicio;
}

void leDadostxt(char* nomeFich, Linha** linhas, Paragem** paragens, int* num_paragens, int* num_linhas) {
    int i;
    char file[50];

    snprintf(file, sizeof (file), "../%s.txt", nomeFich);
    FILE* f = fopen(file, "r");
    if (f == NULL) {
        printf("\n\tErro ao abrir o ficheiro!!\n");
        return;
    }

    (*num_linhas)++;
    *linhas = (Linha *) realloc(*linhas, ((*num_linhas) * sizeof(Linha)));

    int numL=(*num_linhas)-1;

    //Ler o nome da linha
    fgets(((*linhas)+numL)->nome, sizeof((*linhas+numL)->nome), f);
    ((*linhas)+numL)->nome[strcspn((*linhas+numL)->nome, "\n")] = '\0';

    ((*linhas)+numL)->head = NULL;

    //Verifica se existe uma paragem com o mesmo nome
    for (i = 0; i < (*num_linhas) - 1; i++) {
        if (strcmp((*linhas + i)->nome, ((*linhas)+numL)->nome) == 0) {
            printf("\n\tJa existe uma linha com o mesmo nome!\n");
            (*num_linhas)--;
            *linhas = (Linha *) realloc(*linhas, ((*num_linhas) * sizeof(Linha))); //se nao usar cria novamente a mesma linha
            return;
        }
    }

    printf("\n\tLinha: %s", ((*linhas)+numL)->nome);
    printf("\n\t--------------------------------------\n");
    printf("\t%s \t\t%s\n", "Codigo", "Nome");
    printf("\t--------------------------------------\n");
    //Ler as paragens
    char linhaParagem[100];
    while (fgets(linhaParagem, sizeof(linhaParagem), f)) {
        linhaParagem[strcspn(linhaParagem, "\n")] = '\0';
        //Separar o nome da paragem e o código usando o caractere '#'
        char* nome = strtok(linhaParagem, "#");
        char* cod = strtok(NULL, "#");

        nome = cortaespaco(nome);
        cod = cortaespaco(cod);

        int flagexiste=0;
        for (i = 0; i < *num_paragens; i++) {
            if (strcmp((*paragens + i)->nome, nome) == 0 && strcmp((*paragens + i)->codigo, cod) == 0) {
                inserirLinhaParagem(((*linhas)+numL), (*paragens + i));
                printf("\t%s \t\t%s\n", cod, nome);
                flagexiste=1;
                break;
            }
        }
        if(flagexiste==0){
            printf("\tA paragem %s com o codigo %s nao existe!\n", nome, cod);
        }
    }
    printf("\n");
    if(((*linhas)+numL)->head == NULL){
        (*num_linhas)--;
        *linhas = (Linha *) realloc(*linhas, ((*num_linhas) * sizeof(Linha)));
    }
    fclose(f);
}

int verificaPLinha(int *num_linhas, Linha** linhas, char cod[5]){
    int i;
    //Verifica se a paragem está presente em alguma linha
    for (i = 0; i < *num_linhas; i++) {
        Linha_Paragem* curr = (*linhas + i)->head;
        while (curr != NULL) {
            if (strcmp(curr->paragem.codigo, cod) == 0) {
                printf("\tA paragem com o codigo %s pertence a uma linha. Nao pode ser removida!\n\n", cod);
                return 1;
            }
            curr = curr->prox;
        }
    }
    return 0;
}

void atualizar_linha(int* num_linhas, Linha** linhas, Paragem** paragens, int* num_paragens) {
    char nomeLinha[50];
    int opcao;

    printf("\n\t===============");
    printf("\n\tAtualizar Linha");
    printf("\n\t===============\n");
    printf("\tNome da Linha: ");
    scanf(" %[^\n]", nomeLinha);

    int linhaEncontrada = 0;
    for (int i = 0; i < (*num_linhas); i++) {
        if (strcmp((*linhas+i)->nome, nomeLinha) == 0) {
            linhaEncontrada = 1;
            do {
                printf("\n\tEscolha uma opcao:\n");
                printf("\t1. Adicionar paragem\n");
                printf("\t2. Remover paragem\n");
                printf("\t3. Sair\n");
                printf("\tOpcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        adicionaparagens(paragens, (*linhas+i), num_paragens);
                        break;
                    case 2:
                        removeParagem((*linhas+i));
                        break;
                    case 3:
                        printf("\n\tSair\n");
                        break;
                    default:
                        printf("\n\tOpcao invalida! Tente novamente.\n");
                        break;
                }
                if((*linhas+i)->head == NULL){
                    printf("\n\tLinha %s ficou sem paragens e vai ser removida!!\n", (*linhas+i)->nome);
                    for(int j=0; j <= (*num_linhas); j++) {
                        if(strcmp((*linhas+i)->nome, (*linhas+j)->nome) == 0) {
                            for(int k=j; k < (*num_linhas - 1); k++) {
                                (*linhas)[k] = (*linhas)[k + 1];
                            }
                            (*num_linhas)--;
                            *linhas = (Linha *) realloc(*linhas, *num_linhas * sizeof(Linha));
                            return;
                        }
                    }
                }
            } while (opcao != 3);
        }
    }

    if (!linhaEncontrada) {
        printf("\n\tNenhuma linha encontrada com o nome: %s!\n\n", ((*linhas))->nome);
    }
}

void removeParagem(Linha* linha) {
    Linha_Paragem* atual = (linha)->head;
    Linha_Paragem* anterior = NULL;

    char codP[5];

    printf("\n\tInsira o codigo da Paragem ou digite 'sair' para parar: ");
    scanf(" %[^\n]", codP);

    if (strcmp(codP, "sair") == 0) {
        return;
    }
    //Percorre a lista ate encontrar o codigo atual
    while (strcmp(codP, atual->paragem.codigo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) {
        printf("O codigo nao foi encontrado na lista.\n");
        return;
    }
    //Atualizar os ponteiros dos elementos adjacentes
    if (anterior == NULL) {
        //O elemento a ser removido é o primeiro da lista
        (linha)->head = atual->prox;
    } else {
        anterior->prox = atual->prox;
        if (atual->prox != NULL) {
            atual->prox->ant = anterior;
        }
    }
    free(atual);
    printf("\tA paragem foi removida com sucesso!!\n");
}

void adicionaparagens(Paragem** paragens, Linha* linhas,int *num_paragens){
    char nomeP[10];
    int i;

    printf("\n");
    printf("\tInsira o nome da Paragem ou digite 'sair' para parar: ");
    scanf(" %[^\n]", nomeP);

    if (strcmp(nomeP, "sair") == 0) {
        return;
    }

    Paragem* Pcorres = NULL;
    for (i = 0; i < (*num_paragens); i++) {
        if (strcmp((*paragens + i)->nome, nomeP) == 0) {
            Pcorres = (*paragens + i);
            break;
        }
    }

    if (Pcorres == NULL) {
        printf("\tNao existe nenhuma paragem com esse nome!\n");
        return;
    }

    Linha_Paragem* curr = linhas->head;
    while (curr != NULL) {
        if (strcmp(curr->paragem.codigo, Pcorres->codigo) == 0) {
            printf("\tA paragem ja foi adicionada!\n");
            Pcorres = NULL;
            break;
        }
        curr = curr->prox;
    }

    if (Pcorres != NULL) {
        inserirLinhaParagem(linhas, Pcorres);
        printf("\n\tParagem adicionada com sucesso!\n");
    }
}

void calcPercurso(Paragem* inicial, Paragem* final, int* num_linhas, Linha** linhas) {
    Linha* linhasI = NULL;             //array para guardar as linhas que tem a paragem em que vou entrar
    Linha* linhasF = NULL;             //array para guardar as linhas que tem a paragem em que vou sair
    //Paragem* paragemInter = NULL;       //paragem intercecao
    int numLinhasI  = 0;
    int numLinhasF  = 0;
    int fim, indiceI, indiceF, inicio, flag ;
    int i;

    for (i = 0; i < (*num_linhas); i++) {
        Linha_Paragem* current = (*linhas+i)->head;
        while (current != NULL){
            if (strcmp(current->paragem.nome, inicial->nome) == 0) {
                (numLinhasI)++;
                linhasI = (Linha*) realloc(linhasI, numLinhasI * sizeof(Linha));
                indiceI = numLinhasI-1;
                memcpy(&linhasI[indiceI], &(*linhas)[i], sizeof((*linhas)[i]));
            }
            current = current->prox;
        }
    }

    for (i = 0; i < (*num_linhas); i++) {            //Quantidade de linhas que existem
        Linha_Paragem* current = (*linhas+i)->head;
        while (current != NULL){
            if (strcmp(current->paragem.nome, final->nome) == 0) {
                (numLinhasF)++;
                linhasF = (Linha*) realloc(linhasF, numLinhasF * sizeof(struct Linha));
                indiceF = numLinhasF-1;
                memcpy(&linhasF[indiceF], &(*linhas)[i], sizeof((*linhas)[i]));
            }
            current = current->prox;
        }
    }

    for (i = 0; i < numLinhasI; i++) {              //Quantidade de linhas que tem a paragem em que vou entrar
        Linha_Paragem* currentI = (linhasI+i)->head;
        inicio = 0 ;
        flag = 0;
        while (currentI != NULL) {
            for (int j = 0; j < numLinhasF; j++) {      //Quantidade de linhas que tem a paragem onde vou sair
                Linha_Paragem* currentF = (linhasF+j)->head;
                fim = 0;
                while (currentF != NULL) {
                    if (strcmp((currentI)->paragem.nome, (currentF)->paragem.nome)==0){ //linhas comuns linhaI linhasF
                        if (strcmp((linhasI+i)->nome, (linhasF+j)->nome) == 0) {  //DIRETO
                            if(strcmp(currentF->paragem.nome, inicial->nome)==0 && flag != -1){
                                inicio = 0;
                                imprimeDireto(currentF, final->nome,&linhasF[j],inicio);
                                flag = -1;
                            }
                            else if(strcmp(currentF->paragem.nome , final->nome)==0 && flag != -1) {
                                inicio = 1;
                                imprimeDireto(currentF, inicial->nome,&linhasF[j],inicio);
                                flag = -1;
                            }
                        }
                        //N DIRETO
                        else if (strcmp(currentF->paragem.nome, final->nome) != 0 && strcmp(currentF->paragem.nome, inicial->nome) != 0){
                            imprimeSalto(inicio, fim, &linhasI[i], &linhasF[j], inicial->nome, final->nome, currentF->paragem.nome);
                        }
                    }
                    if(strcmp(currentF->paragem.nome , final->nome) == 0) {
                        fim = 1;
                        //ant
                    }
                    currentF = currentF->prox;
                }
            }
            if (strcmp(currentI->paragem.nome , inicial->nome) == 0) {
                inicio = 1;
            }
            currentI = currentI->prox;
        }
    }
}

void imprimeDireto(Linha_Paragem* paragem, char* paragemFinal, Linha* linhaI, int inicio){ //QUANDO E DIRETO
    if(inicio == 0){             //verificar se na lista ligada esta a ler bem ou ao contrario
        Linha_Paragem* currentI = paragem;

        printf("\n\t---------------------------------------------------\n");
        printf ("\tLinha: %s\n", linhaI->nome);
       do{
           printf(" \t%s --> ", currentI->paragem.nome);
           currentI = currentI->prox;
       } while (strcmp(currentI->paragem.nome, paragemFinal) != 0);
        printf(" %s ", currentI->paragem.nome);
        printf("\n\t---------------------------------------------------\n");
        return;
    }
    else if(inicio == 1){
        Linha_Paragem* currentI = NULL;
        Linha_Paragem* currentF = paragem;

        while (strcmp(currentF->paragem.nome, paragemFinal) != 0) {
            currentF = currentF -> prox;
        };

        currentI = currentF;
        currentF = paragem;

        printf("\n\t---------------------------------------------------\n");
        printf ("\tLinha: %s\n", linhaI->nome);
        do{
            printf(" %s --> ", currentI->paragem.nome);
            currentI = currentI->ant;
        }while ((currentI != currentF));
        printf(" %s ", currentI->paragem.nome);
        printf("\n\t---------------------------------------------------\n");
        return;
    }
}

void imprimeSalto(int inicio,int fim, Linha* linhaI, Linha* linhaF,char* paragemInicial,char* paragemFinal,char* paragemInter) { //QUANDO MUDA DE LINHA
    if (inicio == 0 && fim == 0) {

        Linha_Paragem* pInicial = NULL;
        Linha_Paragem* interI = NULL;
        Linha_Paragem* pFinal = NULL;
        Linha_Paragem* interF = NULL;
        Linha_Paragem* currentI = linhaI->head;
        Linha_Paragem* currentF = linhaF->head;

        while (strcmp(currentI->paragem.nome, paragemInicial) != 0) {
            if (strcmp(currentI->paragem.nome, paragemInter) == 0) {
                interI = currentI;
            }
            currentI = currentI->prox;
        }

        pInicial = currentI;

        while (strcmp(currentF->paragem.nome, paragemFinal) != 0) {
            if (strcmp(currentF->paragem.nome, paragemInter) == 0) {
                interF = currentF;
            }
            currentF = currentF->prox;
        }

        pFinal = currentF;
        printf("\n\t-----------------------------------------------------\n");
        printf("\tPrimeira Linha: %s\n", linhaI->nome);

        do{
            printf(" \t%s --> ", pInicial->paragem.nome);
            pInicial = pInicial->ant;
        } while (pInicial != interI);
        printf(" %s --> ", pInicial->paragem.nome);

        printf("\n\tSegunda Linha: %s\n", linhaF->nome);

        do{
            printf(" \t%s --> ", interF->paragem.nome);
            interF = interF->prox;
        } while (interF != pFinal);
        printf(" %s ", pFinal->paragem.nome);

    } else if (inicio == 0 && fim == 1) {

        Linha_Paragem* pInicial = NULL;
        Linha_Paragem* interI = NULL;
        Linha_Paragem* pFinal = NULL;
        Linha_Paragem* interF = NULL;
        Linha_Paragem* currentI = linhaI->head;
        Linha_Paragem* currentF = linhaF->head;

        while (strcmp(currentI->paragem.nome, paragemInicial) != 0) {
            if (strcmp(currentI->paragem.nome, paragemInter) == 0) {
                interI = currentI;
            }
            currentI = currentI->prox;
        }

        pInicial = currentI;

        while (strcmp(currentF->paragem.nome, paragemInter) != 0) {
            if (strcmp(currentF->paragem.nome, paragemFinal) == 0) {
                pFinal = currentF;
            }
            currentF = currentF->prox;
        }

        interF = currentF;

        printf("\n\t-----------------------------------------------------\n");
        printf("\tPrimeira Linha: %s\n", linhaI->nome);

        do{
            printf(" \t%s --> ", pInicial->paragem.nome);
            pInicial = pInicial->ant;
        }while(pInicial != interI);
        printf(" %s --> ", pInicial->paragem.nome);


        printf("\n\tSegunda Linha: %s\n", linhaF->nome);
        do{
            printf(" \t%s --> ", interF->paragem.nome);
            interF = interF->ant;
        } while (interF != pFinal);
        printf(" %s ", pFinal->paragem.nome);

    } else if (inicio == 1 && fim == 0) {

        Linha_Paragem* pInicial = NULL;
        Linha_Paragem* interI = NULL;
        Linha_Paragem* pFinal = NULL;
        Linha_Paragem* interF = NULL;
        Linha_Paragem* currentI = linhaI->head;
        Linha_Paragem* currentF = linhaF->head;

        while (strcmp(currentI->paragem.nome, paragemInter) != 0) {
            if (strcmp(currentI->paragem.nome, paragemInicial) == 0) {
                pInicial = currentI;
            }
            currentI = currentI->prox;
        }

        interI = currentI;

        while (strcmp(currentF->paragem.nome, paragemFinal) != 0) {
            if (strcmp(currentF->paragem.nome, paragemInter) == 0) {
                interF = currentF;
            }
            currentF = currentF->prox;
        }

        pFinal = currentF;

        printf("\n\t-----------------------------------------------------\n");
        printf("\tPrimeira Linha: %s\n", linhaI->nome);
        do{
            printf(" \t%s --> ", pInicial->paragem.nome);
            pInicial = pInicial->prox;
        } while (pInicial != interI);
        printf(" %s --> ", pInicial->paragem.nome);

        printf("\n\tSegunda Linha: %s\n", linhaF->nome);
        do{
            printf(" \t%s --> ", interF->paragem.nome);
            interF = interF->prox;
        } while (interF != pFinal);
        printf(" %s ", pFinal->paragem.nome);

    } else if (inicio == 1 && fim == 1) {

        Linha_Paragem* pInicial = NULL;
        Linha_Paragem* interI = NULL;
        Linha_Paragem* pFinal = NULL;
        Linha_Paragem* interF = NULL;
        Linha_Paragem* currentI = linhaI->head;
        Linha_Paragem* currentF = linhaF->head;

        while (strcmp(currentI->paragem.nome, paragemInter) != 0) {
            if (strcmp(currentI->paragem.nome, paragemInicial) == 0) {
                pInicial = currentI;
            }
            currentI = currentI->prox;
        }
        interI = currentI;

        while (strcmp(currentF->paragem.nome, paragemInter) != 0) {
            if (strcmp(currentF->paragem.nome, paragemFinal) == 0) {
                pFinal = currentF;
            }
            currentF = currentF->prox;
        }

        interF = currentF;

        printf("\n\t-----------------------------------------------------\n");
        printf("\tPrimeira Linha: %s\n", linhaI->nome);
        do{
            printf(" %s --> ", pInicial->paragem.nome);
            pInicial = pInicial->prox;
        } while (pInicial != interI);
        printf(" %s --> ", pInicial->paragem.nome);

        printf("\n\tSegunda Linha: %s\n", linhaF->nome);
        do{
            printf(" %s --> ", interF->paragem.nome);
            interF = interF->ant;
        } while (interF != pFinal);
        printf(" %s ", pFinal->paragem.nome);
    }
}

void freeLinhaParagem(Linha_Paragem* linhaParagem) {
    if (linhaParagem == NULL) {
        return;
    }
    freeLinhaParagem(linhaParagem->prox);
    free(linhaParagem);
}

void freeLinha(Linha** linhas) {
    Linha_Paragem* curr = (*linhas)->head;
    while (curr != NULL) {
        Linha_Paragem* temp = curr;
        curr = curr->prox;
        free(temp);
    }
    (*linhas)->head = NULL;
}


