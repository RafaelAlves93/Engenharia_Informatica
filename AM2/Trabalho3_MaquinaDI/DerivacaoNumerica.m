%   Licenciatura Engenharia Informática - Pós Laboral
%   Matlab .: Atividade03Trabalho - Máquina para Derivação e Integração
%   Professor Disciplina: Arménio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020

function varargout = DerivacaoNumerica(varargin)
% DERIVACAONUMERICA M-file for DerivacaoNumerica.fig
%      DERIVACAONUMERICA, by itself, creates a new DERIVACAONUMERICA or raises the existing
%      singleton*.
%
%      H = DERIVACAONUMERICA returns the handle to a new DERIVACAONUMERICA or the handle to
%      the existing singleton*.
%
%      DERIVACAONUMERICA('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DERIVACAONUMERICA.M with the given input arguments.
%
%      DERIVACAONUMERICA('Property','Value',...) creates a new DERIVACAONUMERICA or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before DerivacaoNumerica_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to DerivacaoNumerica_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help DerivacaoNumerica

% Last Modified by GUIDE v2.5 06-June-2020 20:55:57

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @DerivacaoNumerica_OpeningFcn, ...
                   'gui_OutputFcn',  @DerivacaoNumerica_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT

% --- Executes just before DerivacaoNumerica is made visible.
function DerivacaoNumerica_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to DerivacaoNumerica (see VARARGIN)

% Choose default command line output for DerivacaoNumerica
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes DerivacaoNumerica wait for user response (see UIRESUME)
% uiwait(handles.figureDN);
set(handles.cbGrelha,'Value',1)
set(handles.cbEixos,'Value',1)
set(handles.cbLegenda,'Value',1)

MyAtualizar(handles);

% --- Outputs from this function are returned to the command line.
function varargout = DerivacaoNumerica_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

% --- Executes on button press in pbAtualiza.
function pbAtualiza_Callback(hObject, eventdata, handles)
% hObject    handle to pbAtualiza (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
MyAtualizar(handles);

function eA_Callback(hObject, eventdata, handles)
% hObject    handle to eA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eA as text
%        str2double(get(hObject,'String')) returns contents of eA as a double

% --- Executes during object creation, after setting all properties.
function eA_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function eH_Callback(hObject, eventdata, handles)
% hObject    handle to eH (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eH as text
%        str2double(get(hObject,'String')) returns contents of eH as a double

% --- Executes during object creation, after setting all properties.
function eH_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eH (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function eB_Callback(hObject, eventdata, handles)
% hObject    handle to eB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eB as text
%        str2double(get(hObject,'String')) returns contents of eB as a double

% --- Executes during object creation, after setting all properties.
function eB_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eB (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes when user attempts to close figureDN.
function figureDN_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figureDN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: delete(hObject) closes the figure
set(hObject,'Visible','Off');
delete(hObject);

%close(handles.figureDN,'String');

% --- Função auxiliar associada ao botão Atualizar.
function MyAtualizar(handles)
%handles estrutura de dados com as handles para os objetos...
syms x;
strF=get(handles.tFuncao,'String');
f=@(x) eval(vectorize(char(strF)));
df=diff(f(x));
a=str2num(get(handles.eA,'String'));
h=str2num(get(handles.eH,'String'));
b=str2num(get(handles.eB,'String'));

escolha = find([handles.rbPRO2 ...
    handles.rbREG2...
    handles.rbCENT...
    handles.rbPRO3...
    handles.rbREG3...
    handles.rbTODOS] == get(handles.bgFormulasDNumerica,'SelectedObject'));

PRO2 = 1;
REG2 = 2;
CENT = 3;
PRO3 = 4;
REG3 = 5;
TODOS = 6;

[x,y,dydxPRO2]=NDerivacaoDFP_2PONTOS(f,a,b,h);
[x,y,dydxREG2]=NDerivacaoDFR_2PONTOS(f,a,b,h);
[x,y,dydxCENT]=NDerivacaoDFCENT(f,a,b,h);
[x,y,dydxPRO3]=NDerivacaoDFP_3PONTOS(f,a,b,h);
[x,y,dydxREG3]=NDerivacaoDFR_3PONTOS(f,a,b,h);

dydxExata=eval(df);
erroPRO2=abs(dydxExata-dydxPRO2);
erroREG2=abs(dydxExata-dydxREG2);
erroCENT=abs(dydxExata-dydxCENT);
erroPRO3=abs(dydxExata-dydxPRO3);
erroREG3=abs(dydxExata-dydxREG3);
axes(handles.axes1);

switch (escolha)
    case PRO2
        
        plot(x,y,':bo','LineWidth',0.5);
        hold on
        plot(x,dydxPRO2,'-m+');
        plot(x,dydxExata,'-ks');
        hold off;
        legend('Função','Derivada Pro 2','DExata');
        set(handles.uitabela,'ColumnName',[{'x'},{'y'},{'DNumerica'},{'DExata'},{'Erro'}]);
        set(handles.uitabela,'Data',num2cell([x.',y.',dydxPRO2.',dydxExata.',erroPRO2.']));
        
    case REG2
        
        plot(x,y,':bo','LineWidth',0.5);
        hold on
        plot(x,dydxREG2,'-m+');
        plot(x,dydxExata,'-ks');
        hold off;
        legend('Função','Derivada Reg 2','DExata');
        set(handles.uitabela,'ColumnName',[{'x'},{'y'},{'DNumerica'},{'DExata'},{'Erro'}]);
        set(handles.uitabela,'Data',num2cell([x.',y.',dydxREG2.',dydxExata.',erroREG2.']));
        
    case CENT
        
        plot(x,y,':bo','LineWidth',0.5);
        hold on
        plot(x,dydxCENT,'-m+');
        plot(x,dydxExata,'-ks');
        hold off;
        legend('Função','Derivada Centrada','DExata');
        set(handles.uitabela,'ColumnName',[{'x'},{'y'},{'DNumerica'},{'DExata'},{'Erro'}]);
        set(handles.uitabela,'Data',num2cell([x.',y.',dydxCENT.',dydxExata.',erroCENT.']));
        
    case PRO3
        
        plot(x,y,':bo','LineWidth',0.5);
        hold on
        plot(x,dydxPRO3,'-m+');
        plot(x,dydxExata,'-ks');
        hold off;
        legend('Função','Derivada Pro 3','DExata');
        set(handles.uitabela,'ColumnName',[{'x'},{'y'},{'DNumerica'},{'DExata'},{'Erro'}]);
        set(handles.uitabela,'Data',num2cell([x.',y.',dydxPRO3.',dydxExata.',erroPRO3.']));
        
    case REG3
        
        plot(x,y,':bo','LineWidth',0.5);
        hold on
        plot(x,dydxREG3,'-m+');
        plot(x,dydxExata,'-ks');
        hold off;
        legend('Função','Derivada Reg 3','DExata');
        set(handles.uitabela,'ColumnName',[{'x'},{'y'},{'DNumerica'},{'DExata'},{'Erro'}]);
        set(handles.uitabela,'Data',num2cell([x.',y.',dydxREG3.',dydxExata.',erroREG3.']));
        
    case TODOS
        
        plot(x,y,':bo','LineWidth',0.5);
        hold on
        plot(x,dydxPRO2,'-r');
        plot(x,dydxREG2,'g--');
        plot(x,dydxCENT,'m:');
        plot(x,dydxPRO3,'c-+');
        plot(x,dydxREG3,'b:');
        plot(x,dydxExata,'-k+');
        hold off;
        legend('Função','DerivadaDFP 2P','DerivadaDFR 2P','DerivadaDFC','DerivadaDFP 3P', 'DerivadaDFR 3P','DExata');
        set(handles.uitabela,'ColumnName',[{'x'},{'y'},{'Prog_2P'},{'Reg2_P'},{'Centradas'},{'Prog_3P'},{'Reg_3P'},{'DExata'},...
            {'Erro_DFP2P'},{'Erro_DFR2P'},{'Erro_DFC'},{'Erro_DFP3P'},{'Erro_DFR3P'}]);
        
        set(handles.uitabela,'Data',num2cell([x.',y.',dydxPRO2.',dydxREG2.',dydxCENT.',dydxPRO3.',dydxREG3.',dydxExata.',...
            erroPRO2.', erroREG2.', erroCENT.', erroPRO3.', erroREG3.']));
end

if(~(get(handles.cbEixos,'Value')))
    set(handles.axes1,'Xtick',[]);
    set(handles.axes1,'Ytick',[]);
end

if(get(handles.cbLegenda,'Value'))
    legend('show');
else
    legend('hide');
end

if(get(handles.cbGrelha,'Value'))
    grid on;
else
    grid off;
end

% --------------------------------------------------------------------
%function mDN_Callback(hObject, eventdata, handles)
% hObject    handle to mDN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% --------------------------------------------------------------------

function mDNopcoes_Callback(hObject, eventdata, handles)
% hObject    handle to mDNopcoes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --------------------------------------------------------------------
function mDNweb_Callback(hObject, eventdata, handles)
% hObject    handle to mDNweb (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
web('http://www.mat.ufrgs.br/~fabio/der_int.pdf');

% --------------------------------------------------------------------
function mDNsair_Callback(hObject, eventdata, handles)
% hObject    handle to mDNsair (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close all;

% --- Executes on button press in pbGrafico.
function pbGrafico_Callback(hObject, eventdata, handles)
% hObject    handle to pbGrafico (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

user=getenv('USERPROFILE'); %obtem perfil do utilizador do windows
user=fullfile(user,'\Documents\Export'); %caminho do perfil do utilizador nos documentos

[nome, caminho] = uiputfile({'*.png';'*.pdf'},'Guardar Gráfico Como',user);% Seletor de diretorio e nome do ficheiro
caminho = fullfile(caminho,nome);

if (caminho ~= 0)
    f=figure();
    set(f,'Visible','off');
    f.Position=[461 459 601 362]; %Altera posiçao da figura para caber o gráfico
    
    axes=handles.axes1;
    posicaoInicial=axes.Position; %Guarda posicao da tabela antes de alterar
    axes.Position=[8.40000000000041 3.15384615384638 110.200000000001 23.846153846154]; %Altera posição da tabela
    
    copyobj(axes,gcf); %copia tabela para a janela figura
    axes.Position=posicaoInicial; % repoe a posicao da tabela
    legend('show')
    legend('Location','northwest');
    
    rez=600; %resolucao final
    figpos=getpixelposition(f); %obtem a figura da figura
    resolution=get(0,'ScreenPixelsPerInch');%Obtem Pixeis do ecra
    set(f,'paperunits','inches','papersize',figpos(3:4)/resolution,'paperposition',[0 0 figpos(3:4)/resolution]);%faz calculo para obter posicao real
    
    %Converte a extensão em string
    %%%%%%%%%%%%%%%%%%%%
    
    C=strsplit(nome,'.'); %obtem extensão
    C=C(2);
    ext=strcat('-d',C); %obtem comando com extensão do ficheiro
    ext=strjoin(ext); %converte ext que esta em modo celulas para string
    
    print(f,caminho,ext,['-r',num2str(rez)],'-painters')
    
    close(gcf); %fecha janela figura
end

% --- Executes on button press in pbExportaTab.
function pbExportaTab_Callback(hObject, eventdata, handles)
% hObject    handle to pbExportaTab (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

colunas=get(handles.uitabela,'ColumnName');
colunas=transpose(colunas);

%Obtem os dados da tabela para a variavel Data
Data=get(handles.uitabela,'Data');

%Obtem a profile do windows do utilizador
user=getenv('USERPROFILE');
user=fullfile(user,'\Documents\Export');

%Junta o array com o nome das colunas com os dados
cTabela=array2table(Data,...
    'VariableName',colunas);

[nome, caminho] = uiputfile({'*.xlsx';'*.txt'},'Guardar Ficheiro como',user);% Seletor de diretorio e nome do ficheiro
caminho = fullfile(caminho,nome);

if (caminho ~= 0)
    try 
        writetable(cTabela,caminho);
        disp(['O ficheiro Excel foi guardado em ',caminho,'!'])
        
    catch err
        %Verifica se o erro foi na comunicação do office
        if (findstr('NoCOMServer',err.identifier))
            choice = questdlg(['Nao foi possivel iniciar o Excel para a conversão! '...
                'Deseja exportar a tabela para um ficheiro de texto?'],...
                'Export', ...
                'Sim','Não','Não');

            switch choice
                case 'Sim'
                    [nome, caminho] = uiputfile('*.txt','Guardar Ficheiro como',user);% Seletor de diretorio e nome do ficheiro
                    caminho = fullfile(caminho,nome);
                    
                    writetable(cTabela,caminho);
            end
        end
    end
end

% --- Executes on button press in rbPRO2.
function rbPRO2_Callback(hObject, eventdata, handles)
% hObject    handle to rbPRO2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rbPRO2

% --- Executes on button press in cbGrelha.
function cbGrelha_Callback(hObject, eventdata, handles)
% hObject    handle to cbGrelha (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if(get(hObject,'Value'))
    grid on;
else
    grid off;
end

% --- Executes on button press in cbMarcaPonto.
function cbMarcaPonto_Callback(hObject, eventdata, handles)
% hObject    handle to cbMarcaPonto (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if(get(hObject,'Value'))
    [x,y]=ginput(1);
    gtext({['P(',num2str(x),',',num2str(y),')']})
    (set(hObject,'Value',0));
end

% --- Executes on button press in cbEixos.
function cbEixos_Callback(hObject, eventdata, handles)
% hObject    handle to cbEixos (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if (get(hObject,'Value'))
    MyAtualizar(handles);
    set(handles.cbGrelha,'Enable','on');
else
    set(handles.axes1,'Xtick',[]);
    set(handles.axes1,'Ytick',[]);
    set(handles.cbGrelha,'Enable','off');
end

% --- Executes on button press in cbLegenda.
function cbLegenda_Callback(hObject, eventdata, handles)
% hObject    handle to cbLegenda (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if(get(hObject,'Value'))
    legend('show');
else
    legend('hide');
end
    
% --------------------------------------------------------------------
function mMail_Callback(hObject, eventdata, handles)
% hObject    handle to mMail (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
EnviaMail();
