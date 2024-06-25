
#include "..\util.h"

typedef struct {
    Cliente* clientes;
    Mercado* mercado;
    BOOL continua;
    HANDLE hEvEmpresas;
    SDATA* shm;
    BOOL pause;         //Variável para verificar pause
} TDATA;

typedef struct {
    HANDLE hPipe[MAX_CLIENTES];
    HANDLE hMutex;
    HANDLE hEvOperacoes;
    DWORD id;
    TDATA* Share;
} TDATA_EXTRA;


int PauseCommand(LPVOID param, DWORD segundos) {
    TDATA* td = (TDATA*)param;

    HANDLE hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
    if (hTimer == NULL) {
        _tprintf_s(_T("Erro ao criar Waitable Timer: %d\n"), GetLastError());
        return 1;
    }

    td->pause = TRUE;
    LARGE_INTEGER li;
    li.QuadPart = segundos * -10000000LL;

    if (!SetWaitableTimer(hTimer, &li, 0, NULL, NULL, FALSE)) {
        _tprintf_s(_T("Erro ao definir o tempo do Waitable Timer: %d\n"), GetLastError());
        CloseHandle(hTimer);
        return 1;
    }

    _tprintf_s(_T("Operações suspensas por %ld segundos...\n"), segundos);
    WaitForSingleObject(hTimer, INFINITE);

    _tprintf_s(_T("Tempo de pausa expirado! Operações retomadas!\n"));
    td->pause = FALSE;
    CloseHandle(hTimer);

    return 0;
}

// Thread dos comandos no servidor
DWORD WINAPI Input(LPVOID data) {
    TDATA* td = (TDATA*)data;
    TCHAR cmd[256];
    Empresa aux;
    DWORD nEmpresas;

    TCHAR nome_fich[50] = _T("empresas.txt");

    do {
        _tprintf(_T("Comando: "));
        _fgetts(cmd, 256, stdin);
        cmd[_tcslen(cmd) - 1] = _T('\0');
        if (_tcscmp(cmd, _T("users")) == 0) {
            for (int i = 0; i < td->clientes->numUtilizadores; ++i) {
                if (td->clientes->utilizadores[i].ligado == 1) {
                    _tprintf_s(_T("Cliente: %s, Saldo: %.2f€, Online\n"), td->clientes->utilizadores[i].username,
                        td->clientes->utilizadores[i].saldo);
                }
                else {
                    _tprintf_s(_T("Cliente: %s, Saldo: %.2f€, Offline\n"), td->clientes->utilizadores[i].username,
                        td->clientes->utilizadores[i].saldo);
                }
            }
        }
        // Comando para inserir empresas (ficheiro empresas.txt)
        else if (_tcscmp(cmd, _T("emp")) == 0) {
            if (inicializaEmpresas(td->mercado, nome_fich)) {
                _tprintf_s(_T("Empresas inseridas com sucesso! Total de empresas:%d\n"), td->mercado->numEmpresas);
                for (DWORD i = 0; i < td->mercado->numEmpresas; i++) {
                    _tprintf_s(_T("Empresa: %s, Ações Disponíveis: %d, Preço: %.2f€\n"),
                        td->mercado->empresas[i].nome,
                        td->mercado->empresas[i].AcoesDisponiveis,
                        td->mercado->empresas[i].preco);
                    CopyMemory(&(td->shm->mercado.empresas[i]), &(td->mercado->empresas[i]), sizeof(Empresa));

                }
                td->shm->mercado.numEmpresas = td->mercado->numEmpresas;
                SetEvent(td->hEvEmpresas);
            }
            else {
                _tprintf_s(_T("Erro ao inserir empresas!\n"));
            }
        }
        else if (wcsstr(cmd, _T("addc")) != NULL) {
            nEmpresas = td->mercado->numEmpresas;
            if (swscanf_s(cmd, _T("addc %49s %d %f"), aux.nome, (unsigned)_countof(aux.nome),
                &aux.AcoesDisponiveis, &aux.preco) == 3) {
                BOOL nomeExiste = FALSE;
                //VERIFICA SE JÁ EXISTE UMA EMPRESA COM O MESMO NOME
                for (int i = 0; i < nEmpresas; ++i) {
                    if (_tcscmp(td->mercado->empresas[i].nome, aux.nome) == 0) {
                        nomeExiste = TRUE;
                        break;
                    }
                }
                if (nomeExiste) {
                    _tprintf_s(_T("Já existe uma empresa com o mesmo nome!\n"));
                }
                else {
                    CopyMemory(&(td->mercado->empresas[nEmpresas]), &aux, sizeof(Empresa));
                    CopyMemory(&(td->shm->mercado.empresas[nEmpresas]), &aux, sizeof(Empresa));
                    SetEvent(td->hEvEmpresas);
                    nEmpresas++;
                    td->mercado->numEmpresas = nEmpresas;
                    td->shm->mercado.numEmpresas = nEmpresas;
                }
            }
            else {
                _tprintf_s(_T("Número de parâmetros incorreto!\n"));
            }
        }
        else if (_tcscmp(cmd, _T("listc")) == 0) {
            nEmpresas = td->mercado->numEmpresas;
            if (nEmpresas > 0) {
                for (DWORD i = 0; i < nEmpresas; ++i) {
                    _tprintf_s(_T("Nome: %s, Numero de Ações: %d, Preço: %.2f€\n"), td->mercado->empresas[i].nome,
                        td->mercado->empresas[i].AcoesDisponiveis, td->mercado->empresas[i].preco);
                }
            }
            else {
                _tprintf_s(_T("Não existem empresas disponiveis!\n"));
            }
        }
        else if (wcsstr(cmd, _T("stock")) != NULL) {
            nEmpresas = td->mercado->numEmpresas;
            if (nEmpresas == 0) {
                _tprintf_s(_T("Não existem empresas disponiveis!\n"));
            }
            else {
                if (swscanf_s(cmd, _T("stock %49s %f"), aux.nome, (unsigned)_countof(aux.nome), &aux.preco) == 2) {
                    for (int i = 0; i < nEmpresas; ++i) {
                        if (_tcscmp(td->mercado->empresas[i].nome, aux.nome) == 0) {
                            td->mercado->empresas[i].preco = aux.preco;
                            td->shm->mercado.empresas[i].preco = aux.preco;
                            SetEvent(td->hEvEmpresas);
                        }
                    }
                }
                else {
                    _tprintf_s(_T("Número de parâmetros incorreto!\n"));
                }
            }
        }
        else if (wcsstr(cmd, _T("pause")) != NULL) {
            DWORD segundos;
            if (swscanf_s(cmd, _T("pause %d"), &segundos) == 1) {
                PauseCommand(td, segundos);
            }
            else {
                _tprintf_s(_T("Número de parâmetros incorretos!\n"));
            }
        }
        else {
            _tprintf_s(_T("[SERVIDOR] Comando inválido!\n"));
        }
    } while (_tcscmp(cmd, _T("close")) != 0);

    td->continua = FALSE;
    return 0;
}

// Thread para atender os clientes
DWORD WINAPI AtendeCliente(LPVOID data) {
    TDATA_EXTRA* te = (TDATA_EXTRA*)data;
    TCHAR buf[256];
    TCHAR conc[256];
    DWORD nbytes;
    DWORD flag_empresas, flag_utilizadores;

    HANDLE hPipe;
    DWORD id;

    Utilizador auxu;
    Empresa auxe;

    TCHAR nome_empresa[TAM];
    DWORD acoescompra;
    DWORD acoesvenda;

    WaitForSingleObject(te->hMutex, INFINITE);
    id = te->id;
    hPipe = te->hPipe[id];
    ReleaseMutex(te->hMutex);

    _tprintf_s(_T("[SERVIDOR] À espera de dados do cliente [%d]...\n"), id);
    while (te->Share->continua) {
        flag_utilizadores = 0;
        flag_empresas = 0;
        if (!ReadFile(hPipe, buf, sizeof(buf), &nbytes, NULL)) {
            _tprintf_s(_T("[ERRO] Ler dados do cliente [%d]!\n"), id);
            exit(1);
        }

        buf[nbytes / sizeof(TCHAR)] = '\0';
        _tprintf_s(_T("Li do cliente [%d] a msg: %s\n"), id, buf);

        /*--------------------------------PROCESSAMENTO DOS PEDIDOS DOS CLIENTES-----------------------------------------*/

        //--------------------------------------------COMANDO LOGIN---------------------------------------------------------------
        if (wcsstr(buf, _T("login")) != NULL) {
            _tprintf_s(_T("Tentativa de login\n"));
            if (_stscanf_s(buf, _T("login %49s %49s"), auxu.username, (unsigned)_countof(auxu.username),
                auxu.password, (unsigned)_countof(auxu.password)) == 2) {
                for (int i = 0; i < te->Share->clientes->numUtilizadores; ++i) {
                    if (_tcscmp(auxu.username, te->Share->clientes->utilizadores[i].username) == 0 &&
                        _tcscmp(auxu.password, te->Share->clientes->utilizadores[i].password) == 0) {
                        flag_utilizadores = 1;
                        if (te->Share->clientes->utilizadores[i].ligado == 0) {
                            te->Share->clientes->utilizadores[i].ligado = 1;
                            te->Share->clientes->utilizadores[i].id_cliente = id;
                            _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Login com sucesso!"));
                            if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                                _tprintf(_T("[ERRO] Escrita no pipe!\n"));
                                exit(-1);
                            }
                            _tprintf_s(_T("Escrevi no pipe\n"));
                        }
                        else {
                            _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Utilizador já se encontra autenticado!"));
                            if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                                _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                                exit(-1);
                            }
                        }
                    }
                }
                if (flag_utilizadores == 0) {
                    _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Nome de Utilizador/Password Errado!\n"));
                    if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                        _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                        exit(-1);
                    }
                }

            }
            else {
                _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Número de parâmetros incorreto!"));
                if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                    _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                    exit(-1);
                }
            }
        }
        //--------------------------------------------COMANDO LISTC---------------------------------------------------------------
        else if (_tcscmp(buf, _T("listc")) == 0) {
            ZeroMemory(buf, 256);
            for (int i = 0; i < te->Share->clientes->numUtilizadores; ++i) {
                auxu = te->Share->clientes->utilizadores[i];
                if (auxu.id_cliente == id && auxu.ligado == 1) {
                    flag_utilizadores = 1;
                    if (te->Share->mercado->numEmpresas > 0) {
                        for (int i = 0; i < te->Share->mercado->numEmpresas; ++i) {
                            auxe = te->Share->mercado->empresas[i];
                            swprintf_s(conc, 256, _T("Nome: %s | Ações Disponíveis: %d | Preço: %.2f\n"),
                                auxe.nome, auxe.AcoesDisponiveis, auxe.preco);
                            wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), conc);
                        }
                        if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                            _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                            exit(-1);
                        }
                        break;
                    }
                    else {
                        _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Não existem empresas na bolsa!\n"));
                        if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                            _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                            exit(-1);
                        }
                        break;
                    }
                }
            }
            if (flag_utilizadores == 0) {
                _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Acesso Negado!\n"));
                if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                    _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                    exit(-1);
                }
            }
        }
        //--------------------------------------------COMANDO BALANCE---------------------------------------------------------------
        else if (_tcscmp(buf, _T("balance")) == 0) {
            for (int i = 0; i < te->Share->clientes->numUtilizadores; ++i) {
                auxu = te->Share->clientes->utilizadores[i];
                if (auxu.id_cliente == id && auxu.ligado == 1) {
                    flag_utilizadores = 1;
                    _stprintf_s(buf, 256, _T("Saldo Atual: %.2f"), auxu.saldo);
                    _tprintf_s(_T("Escrevi: %s"), buf);
                    if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                        _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                        exit(-1);
                    }
                }
            }
            if (flag_utilizadores == 0) {
                _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Acesso Negado!\n"));
                if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                    _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                    exit(-1);
                }
            }
        }
        //--------------------------------------------COMANDO BUY---------------------------------------------------------------
        else if (wcsstr(buf, _T("buy")) != NULL && te->Share->pause == FALSE) {
            if ((swscanf_s(buf, _T("buy %49s %d"), nome_empresa, (unsigned)_countof(nome_empresa), &acoescompra) == 2)) {
                for (int i = 0; i < te->Share->mercado->numEmpresas; ++i) {
                    auxe = te->Share->mercado->empresas[i];
                    if (_tcscmp(nome_empresa, auxe.nome) == 0) {
                        flag_empresas = 1;
                        if (auxe.AcoesDisponiveis >= acoescompra) {
                            for (int j = 0; j < te->Share->clientes->numUtilizadores; ++j) {
                                auxu = te->Share->clientes->utilizadores[j];
                                if (auxu.id_cliente == id && auxu.ligado == 1) {
                                    flag_utilizadores = 1;

                                    if (auxu.saldo >= acoescompra * auxe.preco) {
                                        //SE A CARTEIRA ESTIVER VAZIA
                                        if (auxu.nCarteira == 0) {
                                            _tcscpy_s(te->Share->clientes->utilizadores[j].carteira[0].empresa, sizeof(auxu.carteira[0].empresa) / sizeof(TCHAR), nome_empresa);
                                            te->Share->clientes->utilizadores[j].carteira[0].nAcoes = acoescompra;
                                            te->Share->clientes->utilizadores[j].nCarteira++;
                                            te->Share->clientes->utilizadores[j].saldo -= acoescompra * auxe.preco;
                                            te->Share->mercado->empresas[i].AcoesDisponiveis -= acoescompra;
                                            _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Compra realizada com sucesso!"));
                                            if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                                                _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                                                exit(-1);
                                            }
                                            te->Share->shm->recente.nAcoes = acoescompra;
                                            te->Share->shm->recente.preco = auxe.preco;
                                            _tcscpy_s(te->Share->shm->recente.nome, sizeof(te->Share->shm->recente.nome) / sizeof(TCHAR), auxe.nome);
                                            SetEvent(te->hEvOperacoes);
                                        }
                                        else {
                                            for (int n = 0; n < auxu.nCarteira + 1; ++n) {
                                                //SE ENCONTRAR A EMPRESA NA CARTEIRA
                                                if (_tcscmp(auxe.nome, auxu.carteira[n].empresa) == 0) {
                                                    te->Share->clientes->utilizadores[j].carteira[n].nAcoes += acoescompra;
                                                    te->Share->clientes->utilizadores[j].saldo -= acoescompra * auxe.preco;
                                                    te->Share->mercado->empresas[i].AcoesDisponiveis -= acoescompra;
                                                    _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Compra realizada com sucesso!"));
                                                    if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                                                        _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                                                        exit(-1);
                                                    }
                                                    te->Share->shm->recente.nAcoes = acoescompra;
                                                    te->Share->shm->recente.preco = auxe.preco;
                                                    _tcscpy_s(te->Share->shm->recente.nome, sizeof(te->Share->shm->recente.nome) / sizeof(TCHAR), auxe.nome);
                                                    SetEvent(te->hEvOperacoes);
                                                    break;
                                                }
                                                //SE A EMPRESA NÃO EXISTIR NA CARTEIRA E ESTA TER ESPAÇO
                                                if (_tcscmp(auxe.nome, auxu.carteira[n].empresa) != 0 && i + 1 == auxu.nCarteira) {
                                                    _tcscpy_s(te->Share->clientes->utilizadores[j].carteira[auxu.nCarteira].empresa, sizeof(auxu.carteira[auxu.nCarteira].empresa) / sizeof(TCHAR), nome_empresa);
                                                    te->Share->clientes->utilizadores[j].carteira[auxu.nCarteira].nAcoes = acoescompra;
                                                    te->Share->clientes->utilizadores[j].nCarteira++;
                                                    te->Share->clientes->utilizadores[j].saldo -= acoescompra * auxe.preco;
                                                    te->Share->mercado->empresas[i].AcoesDisponiveis -= acoescompra;
                                                    _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Compra realizada com sucesso!"));
                                                    if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                                                        _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                                                        exit(-1);
                                                    }
                                                    te->Share->shm->recente.nAcoes = acoescompra;
                                                    te->Share->shm->recente.preco = auxe.preco;
                                                    _tcscpy_s(te->Share->shm->recente.nome, sizeof(te->Share->shm->recente.nome) / sizeof(TCHAR), auxe.nome);
                                                    SetEvent(te->hEvOperacoes);
                                                    break;
                                                }
                                                //SE A CARTEIRA ESTIVER CHEIA
                                                if (_tcscmp(auxe.nome, auxu.carteira[n].empresa) != 0 && i + 1 == auxu.nCarteira && auxu.nCarteira == 5) {
                                                    _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Carteira cheia!"));
                                                    if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                                                        _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                                                        exit(-1);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else {
                                        _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Saldo Indisponível"));
                                        if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                                            _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                                            exit(-1);
                                        }
                                    }
                                }
                            }
                            //SE CLIENTE NÃO FOR ENCONTRADO OU SE NÃO ESTIVER AUTENTICADO
                            if (flag_utilizadores == 0) {
                                _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Acesso Negado!\n"));
                                if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                                    _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                                    exit(-1);
                                }
                            }
                        }
                        else {
                            _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Número de Ações indisponível!"));
                            if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                                _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                                exit(-1);
                            }
                        }
                    }
                }
                //SE NÃO ENCONTRAR EMPRESA
                if (flag_empresas == 0) {
                    _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Empresa Não Encontrada"));
                    if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                        _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                        exit(-1);
                    }
                }
            }
            else {
                _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Número de parâmetros incorreto!"));
                if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                    _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                    exit(-1);
                }
            }
        }
        // Operação em pause
        else if (wcsstr(buf, _T("buy")) != NULL && te->Share->pause == TRUE) {
            _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Operações suspensas!"));
            if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                exit(-1);
            }
        }

        //--------------------------------------------COMANDO SELL---------------------------------------------------------------
        else if (wcsstr(buf, _T("sell")) != NULL && te->Share->pause == FALSE) {
            if ((swscanf_s(buf, _T("sell %49s %d"), nome_empresa, (unsigned)_countof(nome_empresa), &acoesvenda) == 2)) {
                for (int n = 0; n < te->Share->clientes->numUtilizadores; ++n) {
                    auxu = te->Share->clientes->utilizadores[n];
                    if (auxu.id_cliente == id && auxu.ligado == 1) {
                        flag_utilizadores = 1;
                        if (auxu.nCarteira == 0) {
                            _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Não Possui Ações!"));
                            if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                                _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                                exit(-1);
                            }
                            break;
                        }
                        for (int i = 0; i < auxu.nCarteira; ++i) {
                            if (_tcscmp(auxu.carteira[i].empresa, nome_empresa) == 0 && auxu.carteira[i].nAcoes >= acoesvenda) {
                                flag_empresas = 1;
                                for (int j = 0; j < te->Share->mercado->numEmpresas; ++j) {
                                    auxe = te->Share->mercado->empresas[j];
                                    if (_tcscmp(auxe.nome, nome_empresa) == 0) {
                                        te->Share->mercado->empresas[j].AcoesDisponiveis += acoesvenda;
                                        te->Share->clientes->utilizadores[n].saldo += acoesvenda * auxe.preco;
                                        te->Share->clientes->utilizadores[n].carteira[i].nAcoes -= acoesvenda;
                                        _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Venda realizada com sucesso!"));
                                        if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                                            _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                                            exit(-1);
                                        }
                                        te->Share->shm->recente.nAcoes = acoesvenda;
                                        te->Share->shm->recente.preco = auxe.preco;
                                        _tcscpy_s(te->Share->shm->recente.nome, sizeof(te->Share->shm->recente.nome) / sizeof(TCHAR), auxe.nome);
                                        SetEvent(te->hEvOperacoes);
                                        break;
                                    }
                                }
                            }
                            else if (_tcscmp(auxu.carteira[i].empresa, nome_empresa) == 0 && auxu.carteira[i].nAcoes < acoesvenda) {
                                _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Não possui ações suficientes!"));
                                if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                                    _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                                    exit(-1);
                                }
                                break;
                            }
                        }
                        if (flag_empresas == 0) {
                            _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Empresa Não Encontrada!\n"));
                            if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                                _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                                exit(-1);
                            }
                            break;
                        }
                    }
                }
                if (flag_utilizadores == 0) {
                    _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Acesso Negado!\n"));
                    if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                        _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                        exit(-1);
                    }
                }

            }
            else {
                _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Número de parâmetros incorreto!"));
                if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                    _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                    exit(-1);
                }
            }
        }
        // Operação em pause
        else if (wcsstr(buf, _T("sell")) != NULL && te->Share->pause == TRUE) {
            _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Operações suspensas!"));
            if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                exit(-1);
            }
        }

        //--------------------------------------------COMANDO EXIT (CLIENTE ENCERROU)---------------------------------------------------------------
        else if (_tcscmp(buf, _T("exit")) == 0) {
            for (int i = 0; i < te->Share->clientes->numUtilizadores; ++i) {
                auxu = te->Share->clientes->utilizadores[i];
                if (auxu.id_cliente == id && auxu.ligado == 1) {
                    te->Share->clientes->utilizadores[i].id_cliente = -1;
                    te->Share->clientes->utilizadores[i].ligado = 0;
                    break;
                }
                else if (auxu.id_cliente == id && auxu.ligado == 0) {
                    te->Share->clientes->utilizadores[i].id_cliente = -1;
                    break;
                }
            }
            _tprintf_s(_T("O cliente [%d] saiu\n"), id);
            break;
        }
        else {
            _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Comando Inválido"));
            if (!WriteFile(hPipe, buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
                _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
                exit(-1);
            }
        }
        //--------------------------------------------COMANDO EXIT (CLIENTE FECHOU)---------------------------------------------------------------
    }

    FlushFileBuffers(hPipe);
    if (!DisconnectNamedPipe(hPipe)) {
        _tprintf_s(_T("[ERRO] Desconetar o pipe!\n"));
        exit(-1);
    }
    CloseHandle(hPipe);

    return 0;
}

BOOL inicializaServidor(Controlo* dados) {
    dados->hMutex = CreateMutex(NULL, FALSE, NULL);
    if (dados->hMutex == NULL) {
        _tprintf_s(_T("[SERVIDOR] Erro ao criar o mutex.\n"));
        return FALSE;
    }

    dados->cliLigados = 0;                  //Inicializa o numero de clientes ligados a 0

    //Verificar se o mutex ja existe
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        _tprintf_s(_T("[SERVIDOR] Já existe uma instância do servidor em execução.\n"));
        CloseHandle(dados->hMutex);
        return FALSE;
    }
    //Não há outra instância do servidor em execução
    return TRUE;
}

void welcome() {
    _tprintf_s(_T("\t\t\t -----------------------\n"));
    _tprintf_s(_T("\t\t\t  BEM-VINDO AO SERVIDOR\n"));
    _tprintf_s(_T("\t\t\t -----------------------\n\n"));
}

BOOL registoChave() {
    DWORD estado;
    DWORD valor = MAX_CLIENTES;
    HKEY chave;                             //HKEY_CURRENT_USER\SOFTWARE\TP_SO2

    if (RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software\\TP\\SO2"), 0, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &chave, &estado) != ERROR_SUCCESS) {    //Se nao der erro:   
        _tprintf_s(_T("[SERVIDOR] Erro %d ao criar chave no REGISTRY"), GetLastError());
        return 1;
    }
    else {  //Se correu bem
        if (estado == REG_CREATED_NEW_KEY) {
            _tprintf_s(TEXT("[SERVIDOR] Chave foi criada!\n"));
            _tprintf_s(_T("[SERVIDOR] Valor %d escrito na chave de registo com sucesso!\n"), valor);

        }
        else if (estado == REG_OPENED_EXISTING_KEY) {
            _tprintf_s(TEXT("[SERVIDOR] Chave foi Aberta!\n"));
        }
    }

    //VERIFICAR DEPOIS SE ESTE CAMPO VAI PARA MEMORIA PARTILHADA! &valor
    if (RegSetValueEx(chave, _T("NCLIENTES"), 0, REG_DWORD, (const BYTE*)&valor, sizeof(DWORD)) != ERROR_SUCCESS) {   //Se der erro:
        _tprintf_s(_T("[SERVIDOR] Erro %d ao escrever no REGISTRY"), GetLastError());
        RegCloseKey(chave);
        return 1;
    }


    RegCloseKey(chave);
    return 0;
}

// leitura do ficheiro de clientes
BOOL InicializaClientes(Cliente* pc, TCHAR* nome_fich) {
    FILE* fich;
    Utilizador aux;
    DWORD ncli = 0;

    if (_wfopen_s(&fich, nome_fich, _T("r")) != 0) {
        _tprintf_s(_T("[ERRO] Abertura ficheiro clientes: %d\n"), GetLastError());
        exit(-1);
    }
    while (fwscanf_s(fich, _T("%49s %49s %f"), aux.username, (unsigned)_countof(aux.username), aux.password,
        (unsigned)_countof(aux.password), &aux.saldo) == 3) {
        aux.ligado = 0;
        aux.id_cliente = -1;
        aux.nCarteira = 0;
        CopyMemory(&(pc->utilizadores[ncli]), &aux, sizeof(Utilizador));
        ncli++;
    }
    pc->numUtilizadores = ncli;
    return TRUE;
}

// leitura do ficheiro de empresas
BOOL inicializaEmpresas(Mercado* pe, TCHAR* nome_fich) {
    FILE* fich;
    Empresa aux;
    DWORD nEmpresas = pe->numEmpresas;

    if (_wfopen_s(&fich, nome_fich, _T("r")) != 0) {
        _tprintf(_T("[ERRO] Abertura ficheiro empresas: %d\n"), GetLastError());
        return FALSE;
    }
    while (fwscanf_s(fich, _T("%49s %d %f"), aux.nome, (unsigned)_countof(aux.nome), &aux.AcoesDisponiveis, &aux.preco) == 3) {
        // Verificar se o nome contem apenas uma palavra
        if (_tcschr(aux.nome, _T(' ')) != NULL) {
            _tprintf(_T("[ERRO] Nome da empresa inválido: %s\n"), aux.nome);
            continue;
        }
        // Verificar se ja existe uma empresa com o mesmo nome
        BOOL existe = FALSE;
        for (DWORD i = 0; i < nEmpresas; i++) {
            if (_tcscmp(pe->empresas[i].nome, aux.nome) == 0) {
                _tprintf(_T("[ERRO] Empresa duplicada: %s\n"), aux.nome);
                existe = TRUE;
                break;
            }
        }
        // Adicionar a empresa se não for duplicada e se não ultrapassar o limite
        if (!existe) {
            if (nEmpresas >= MAX_EMPRESAS) {
                _tprintf(_T("[ERRO] Limite máximo de empresas atingido: %d\n"), MAX_EMPRESAS);
                fclose(fich);
                return FALSE;
            }
            CopyMemory(&(pe->empresas[nEmpresas]), &aux, sizeof(Empresa));    //nEmpresas é a posiçao do array onde vai ser inserida a empresa
            nEmpresas++;
        }
    }
    fclose(fich);

    pe->numEmpresas = nEmpresas;
    return TRUE;
}

int _tmain(int argc, LPTSTR argv[]) {
    int r;
    Cliente clientes;
    Mercado mercado;
    TDATA tdata;
    TDATA_EXTRA td_extra[MAX_CLIENTES];
    Controlo dados_servidor;
    DWORD nbytes;
    TCHAR buf[256];

    HANDLE hThreadComandos, hThreadClientes[MAX_CLIENTES], hEventoEmp, hEventoOper;


#ifdef UNICODE 
    r = _setmode(_fileno(stdin), _O_WTEXT);
    r = _setmode(_fileno(stdout), _O_WTEXT);
    r = _setmode(_fileno(stderr), _O_WTEXT);
#endif

    //Verifica se outra instancia do servidor esta em execução
    if (!inicializaServidor(&dados_servidor)) {
        return 1;
    }

    // verifica se leu o ficheiro de clientes
    if (argc < 2) {
        _tprintf_s(_T("Numero de parametros incorreto!\n"));
        exit(-1);
    }

    clientes.numUtilizadores = 0;
    mercado.numEmpresas = 0;
    tdata.pause = FALSE;

    //-------------------------------------------------MEMORIA PARTILHADA-------------------------------------------
    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MAX_EMPRESAS * sizeof(SDATA), NOME_MEMORIA_PARTILHADA);
    if (hMapFile == NULL) {
        _tprintf_s(_T("Erro ao criar o arquivo de mapeamento da memória partilhada: %d\n"), GetLastError());
        return 1;
    }

    tdata.shm = (SDATA*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (tdata.shm == NULL) {
        _tprintf_s(_T("Erro ao mapear a memória partilhada: %d\n"), GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    hEventoEmp = CreateEvent(NULL, FALSE, FALSE, NOME_EVENTO_ALTERACAO_EMPRESAS);
    hEventoOper = CreateEvent(NULL, FALSE, FALSE, NOME_EVENTO_ESCRITA_COMPLETA);
    //---------------------------------------------------------------------------------------------------------------


    welcome();
    registoChave();
    InicializaClientes(&clientes, argv[1]);


    tdata.clientes = &clientes;
    tdata.mercado = &mercado;
    tdata.continua = TRUE;
    tdata.hEvEmpresas = hEventoEmp;
    tdata.shm->mercado.numEmpresas = 0;

    hThreadComandos = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Input, (LPVOID)&tdata, 0, NULL);

    do {
        dados_servidor.hPipe = CreateNamedPipe(NOME_PIPE, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 0, 0, 0, NULL);
        if (dados_servidor.hPipe == INVALID_HANDLE_VALUE) {
            _tprintf_s(_T("[ERRO] Falha ao criar o pipe: %d\n"), GetLastError());
            return 1;
        }

        if (ConnectNamedPipe(dados_servidor.hPipe, NULL)) {
            _tprintf_s(_T("[SERVIDOR] Cliente conectado:[%d]\n"), dados_servidor.cliLigados);

            WaitForSingleObject(dados_servidor.hMutex, INFINITE);
            if (dados_servidor.cliLigados < MAX_CLIENTES) {
                td_extra[dados_servidor.cliLigados].hPipe[dados_servidor.cliLigados] = dados_servidor.hPipe;
            }
            ReleaseMutex(dados_servidor.hMutex);

            td_extra[dados_servidor.cliLigados].hEvOperacoes = hEventoOper;
            td_extra[dados_servidor.cliLigados].id = dados_servidor.cliLigados;
            td_extra[dados_servidor.cliLigados].hMutex = dados_servidor.hMutex;
            td_extra[dados_servidor.cliLigados].Share = &tdata;
            hThreadClientes[dados_servidor.cliLigados] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AtendeCliente,
                (LPVOID)&td_extra[dados_servidor.cliLigados], 0, NULL);
            dados_servidor.cliLigados++;
        }
        else {
            _tprintf_s(_T("[SERVIDOR] Erro ao conectar o cliente: %d\n"), GetLastError());
            exit(-1);
        }
    } while (tdata.continua);

    // Esperar que os clientes terminem
    for (int i = 0; i < dados_servidor.cliLigados; ++i) {
        _tcscpy_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Servidor A Encerrar!"));
        if (!WriteFile(td_extra[i].hPipe[i], buf, (DWORD)_tcslen(buf) * sizeof(TCHAR), &nbytes, NULL)) {
            _tprintf_s(_T("[ERRO] Escrita no pipe!\n"));
            exit(-1);
        }
        FlushFileBuffers(td_extra[i].hPipe[i]);
        if (!DisconnectNamedPipe(td_extra[i].hPipe[i])) {
            _tprintf_s(TEXT("[ERRO] Desligar o pipe! (DisconnectNamedPipe)"));
            exit(-1);
        }
        CloseHandle(td_extra[i].hPipe[i]);
    }

    WaitForSingleObject(hThreadComandos, INFINITE);
    WaitForSingleObject(hThreadClientes, INFINITE);
    CloseHandle(hThreadComandos);
    CloseHandle(hThreadClientes);
    CloseHandle(td_extra->hMutex);
    CloseHandle(hEventoEmp);
    CloseHandle(hEventoOper);

    return 0;
}
