%   Licenciatura Engenharia Informática - Pós Laboral
%   Matlab .: Atividade03Trabalho - Máquina para Derivação e Integração
%   Professor Disciplina: Arménio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020

function varargout = IntegracaoNumerica(varargin)
% INTEGRACAONUMERICA MATLAB code for IntegracaoNumerica.fig
%      INTEGRACAONUMERICA, by itself, creates a new INTEGRACAONUMERICA or raises the existing
%      singleton*.
%
%      H = INTEGRACAONUMERICA returns the handle to a new INTEGRACAONUMERICA or the handle to
%      the existing singleton*.
%
%      INTEGRACAONUMERICA('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in INTEGRACAONUMERICA.M with the given input arguments.
%
%      INTEGRACAONUMERICA('Property','Value',...) creates a new INTEGRACAONUMERICA or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before IntegracaoNumerica_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to IntegracaoNumerica_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text5 to modify the response to help IntegracaoNumerica

% Last Modified by GUIDE v2.5 06-Jun-2020 23:27:35

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @IntegracaoNumerica_OpeningFcn, ...
                   'gui_OutputFcn',  @IntegracaoNumerica_OutputFcn, ...
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

% --- Executes just before IntegracaoNumerica is made visible.
function IntegracaoNumerica_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to IntegracaoNumerica (see VARARGIN)

% Choose default command line output for IntegracaoNumerica
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);


% UIWAIT makes IntegracaoNumerica wait for user response (see UIRESUME)
% uiwait(handles.figura_extra);

% vai buscar os dados á primeira GUI MAQUINA DE INTEGRAÇAO
mainObject=findobj('Tag','figureP');
if ~isempty(mainObject)
    mainData=guidata(mainObject);
    
    if get(mainData.rbF,'value') == 1
        select=get(mainData.popupmenuF,'Value');
        value=get(mainData.popupmenuF,'String'); 
        set(handles.eF,'String',value(select));
    else
        select=get(mainData.eG,'String');
        set(handles.eF,'String',select);
    
    end
% else
    set(handles.cbGrelha,'Value',1);
    set(handles.cbEixos,'Value',1);
    set(handles.cbFill,'Value',1);
    set(handles.cbLegenda,'Value',1);
    MyAtualizar(handles);
end

% --- Outputs from this function are returned to the command line.
function varargout = IntegracaoNumerica_OutputFcn(hObject, eventdata, handles) 
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

function MyAtualizar(handles)
testeB=MException('MATLAB:Act:badnum',' Introduza um numero superior a " a " para " b ".');
testeAeB=MException('MATLAB:Act:badnum',' Introduza numeros para "a" e  " b " .');
testeN=MException('matlab:actualiza:badN',' Introduza um numero inteiro par para " n " .');

hGUIMD=findobj('Tag','figureP'); 

if ~isempty(hGUIMD)
%     try
        MDData=guidata(hGUIMD);
        syms x;
        strF  = get(handles.eF, 'String');
        f     = @(x) eval(vectorize(char(strF)));
        a     = str2num(get(handles.eA, 'String'));
        n     = str2num(get(handles.eN, 'String'));
        b     = str2num(get(handles.eB, 'String'));
        
        %validacao de parametros
        
    if b<=a
        throw(testeB)
    end
    
    if ~(isnumeric(a)) && ~(isnumeric(b))
        throw(testeAeB)
    end
    
        escolha = find([handles.rbSimpson ...
                        handles.rbTrapezios ... 
                        handles.rbTodos] == get(handles.uibuttongroup1,'SelectedObject'));

        RSIMPSON = 1; 
        RTRAPEZIO = 2;
        TODOS = 3;

        x=a:(b-a)/n:b;
        y=f(x);
        %calcula valor do integral(valor exacto)
        Calc_Integral=integral(f,a,b);
        %calcula atraves da regra de simpson
        xyRSIMPSON = RSimpson(f,a,b,n);  
        erroSimpson=abs(Calc_Integral-xyRSIMPSON);
        %calculo atraves da regra do trapézio
        xyRTRAPEZIO = RTrapezios(f,a,b,n);
        erroTrapezios = abs(Calc_Integral - xyRTRAPEZIO);


      switch(escolha)

          case RSIMPSON
                if(mod(n,2))
                    throw(testeN)
                end
                
                plot(x,y,'--m+', 'LineWidth',0.5);
                if(get(handles.cbFill,'Value'))
                    fill(x,y,[0.6 0.2 0]);
                end
                legend('Regra Simpson');
                set(handles.uitable,'ColumnName',[{'Solucao_Exata'},{'Valor_Aproximado'},{'Erro_Simpson'}]);
                set(handles.uitable,'Data',num2cell([Calc_Integral,xyRSIMPSON,erroSimpson]));

           case RTRAPEZIO

                plot(x,y,':r+', 'LineWidth',1);
                if(get(handles.cbFill,'Value'))
                    fill(x,y,[0 0.4 0]);
                end
                legend('Regra Trapezios');
                set(handles.uitable,'ColumnName',[{'Solucao_Exata'},{'Valor_Aproximado'},{'Erro_Trapezios'}]);
                set(handles.uitable,'Data',num2cell([Calc_Integral,xyRTRAPEZIO,erroTrapezios]));

           case TODOS

                plot(x,y,':m+', 'LineWidth',0.5);
                
                plot(x,y,'--b*', 'LineWidth',0.5);
                
                
                if(get(handles.cbFill,'Value'))
                    fill(x,y,[0 0 0.6]);
                end
                legend('Exata');
                set(handles.uitable,'ColumnName',[{'Solucão Exata'},{'Regra Simpson'},{'Erro Simpson'},{'Regra Trapezios'},{'Erro Trapezios'}]);
                set(handles.uitable,'Data',num2cell([Calc_Integral,xyRSIMPSON,erroSimpson,xyRTRAPEZIO,erroTrapezios]));
      end
      hold off;
             
%     catch Me
%         errordlg(['Ocorreu um Erro: ' Me.message],'Erro','modal');
%     end
end
if(~(get(handles.cbEixos,'Value')))
    set(handles.axes,'Xtick',[]);
    set(handles.axes,'Ytick',[]);
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

function eA_Callback(hObject, eventdata, handles)
% hObject    handle to eA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eA as text5
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

function eN_Callback(hObject, eventdata, handles)
% hObject    handle to text5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of text5 as text5
%        str2double(get(hObject,'String')) returns contents of text5 as a double

% --- Executes during object creation, after setting all properties.
function eN_CreateFcn(hObject, eventdata, handles)
% hObject    handle to text5 (see GCBO)
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

% Hints: get(hObject,'String') returns contents of eB as text5
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

% --- Executes on button press in pbExportaTabela.
function pbExportaTabela_Callback(hObject, eventdata, handles)
% hObject    handle to pbExportaTabela (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
colunas=get(handles.uitable,'ColumnName');
colunas=transpose(colunas);

%Obtem os dados da tabela para a variavel Data
Data=get(handles.uitable,'Data');

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

% --- Executes on button press in pbExportGrafico.
function pbExportGrafico_Callback(hObject, eventdata, handles)
% hObject    handle to pbExportGrafico (see GCBO)
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
    
    axes=handles.axes;
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

function eF_Callback(hObject, eventdata, handles)
% hObject    handle to eF (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eF as text5
%        str2double(get(hObject,'String')) returns contents of eF as a double

% --- Executes during object creation, after setting all properties.
function eF_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eF (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes during object creation, after setting all properties.
function cbGrupo_CreateFcn(hObject, eventdata, handles)
% hObject    handle to cbGrupo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% --- Executes on button press in cbGrelha.
function cbGrelha_Callback(hObject, eventdata, handles)
% hObject    handle to cbGrelha (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of cbGrelha
if(get(hObject,'Value'))
    grid on;
else
    grid off;
end

% --- Executes on button press in cbFill.
function cbFill_Callback(hObject, eventdata, handles)
% hObject    handle to cbFill (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of cbFill
MyAtualizar(handles);        

% --- Executes on button press in cbEixos.
function cbEixos_Callback(hObject, eventdata, handles)
% hObject    handle to cbEixos (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of cbEixos
if (get(hObject,'Value'))
    MyAtualizar(handles);
    set(handles.cbGrelha,'Enable','on');
else
    set(handles.axes,'Xtick',[]);
    set(handles.axes,'Ytick',[]);
    set(handles.cbGrelha,'Enable','off');
end

% --- Executes on button press in cbLegenda.
function cbLegenda_Callback(hObject, eventdata, handles)
% hObject    handle to cbLegenda (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of cbLegenda
if(get(hObject,'Value'))
    legend('show');
else
    legend('hide');
end

% --------------------------------------------------------------------
function mIN_Callback(hObject, eventdata, handles)
% hObject    handle to mIN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --------------------------------------------------------------------
function mINSair_Callback(hObject, eventdata, handles)
% hObject    handle to mINSair (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close all
