% MN_PVI_GUI Metodos Numericos para resolucao de PVI com GUI

%   y'= f(t,y) com t=[a, b] e y(a)=y0 condicao inicial

% INPUT:
%   f - funcao do segundo membro da Equacao Diferencial
%   [a, b] - extremos do intervalo da variavel independente t
%   n - numero de subintervalos ou iteracoes do metodo
%   y0 - condicao inicial t=a -> y=y0
%   Metodo - {Euler, RK2, RK4, Adams Bashforth Moulton}

% OUTPUT: 
%   y - vector das aproximacoes discretas da solucao exacta
%   Tabela das solucoes aproximadas, solucao exata e erros
%   Grafico das aproximacoes e da solucao exata

%Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%Data: 03/05/2020

function varargout = MN_PVI_GUI(varargin)
% MN_PVI_GUI M-file for MN_PVI_GUI.fig
%      MN_PVI_GUI cria um novo MN_PVI_GUI ou aumenta o existente
%
%      H = MN_PVI_GUI returns the handle to a new MN_PVI_GUI or the handle to
%      the existing singleton*.
%
%      MN_PVI_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MN_PVI_GUI.M with the given input arguments.
%
%      MN_PVI_GUI('Property','Value',...) creates a new MN_PVI_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before MN_PVI_GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to MN_PVI_GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help MN_PVI_GUI

% Last Modified by GUIDE v2.5 03-May-2020 17:59:28

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @MN_PVI_GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @MN_PVI_GUI_OutputFcn, ...
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

% --- Executes just before MN_PVI_GUI is made visible.
function MN_PVI_GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to MN_PVI_GUI (see VARARGIN)

% Choose default command line output for MN_PVI_GUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes MN_PVI_GUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% Actualizar a inteface quando aplicacao e iniciada.
Actualiza(handles);

% --- Outputs from this function are returned to the command line.
function varargout = MN_PVI_GUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

function eF_Callback(hObject, eventdata, handles)
% hObject    handle to eF (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eF as text
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

function eN_Callback(hObject, eventdata, handles)
% hObject    handle to eN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eN as text
%        str2double(get(hObject,'String')) returns contents of eN as a double

% --- Executes during object creation, after setting all properties.
function eN_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function eY0_Callback(hObject, eventdata, handles)
% hObject    handle to eY0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eY0 as text
%        str2double(get(hObject,'String')) returns contents of eY0 as a double

% --- Executes during object creation, after setting all properties.
function eY0_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eY0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

% --- Executes when selected object is changed in bSelect.
function bSelect_SelectionChangeFcn(hObject, eventdata, handles)
% hObject    handle to the selected object in bSelect 
% eventdata  structure with the following fields (see UIBUTTONGROUP)
%	EventName: string 'SelectionChanged' (read only)
%	OldValue: handle of the previously selected object or empty if none was selected
%	NewValue: handle of the currently selected object
% handles    structure with handles and user data (see GUIDATA)
Actualiza(handles);

% --- Executes on button press in bActualizar.
function bActualizar_Callback(hObject, eventdata, handles)
% hObject    handle to bActualizar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
Actualiza(handles);

function Actualiza(handles)
% handles    structure with handles and user data (see GUIDATA)
clc 
% Obter uma funcao do tipo (t,y) valida
fs  =  get(handles.eF,'String');
f   =  @(t,y) eval(vectorize(fs));

try
   testF = f(sym('t'),sym('y'));
catch
    % Caso a funcao nao seja valida
    set(handles.eF, 'BackgroundColor', 'red');
    set(handles.eF, 'ForegroundColor', 'white');
    errordlg(['Introduza uma funcao do tipo f(t,y)!'],'Funcao Invalida','modal');
    return;
end

% Caso a funcao seja valida voltamos as propriedades originais
set(handles.eF, 'BackgroundColor', 'white');
set(handles.eF, 'ForegroundColor', 'black');

% Obter e validar o inicio do intervalo
a = str2num(get(handles.eA, 'String'));
if ~isscalar(a)
    set(handles.eA, 'BackgroundColor', [0.86 0.21 0.22]);
    set(handles.eA, 'ForegroundColor', 'white');
    errordlg(['Valor de A invalido!'],'Parametro Invalido','modal');
    return;
else
    set(handles.eA, 'BackgroundColor', 'white');
    set(handles.eA, 'ForegroundColor', 'black');
end

% Obter e validar o fim do intervalo
b = str2num(get(handles.eB, 'String'));
if ~isscalar(b)
    set(handles.eB, 'BackgroundColor', [0.86 0.21 0.22]);
    set(handles.eB, 'ForegroundColor', 'white');
    errordlg(['Valor de B invalido!'],'Parametro Invalido','modal');
    return;
else
    set(handles.eB, 'BackgroundColor', 'white');
    set(handles.eB, 'ForegroundColor', 'black');
end

% validar que o fim do intervalo e maior que o inicio do intervalo
if b < a
    set(handles.eA, 'BackgroundColor', [0.86 0.21 0.22]);
    set(handles.eA, 'ForegroundColor', 'white');
    set(handles.eB, 'BackgroundColor', [0.86 0.21 0.22]);
    set(handles.eB, 'ForegroundColor', 'white');
    errordlg(['Valor de B tem de ser maior que A!'],'Parametro Invalido','modal');
    return;
end

n = str2num(get(handles.eN, 'String'));
% mod(n,1) ~= 0 -> validar que o numero e inteiro (str2num devolve um double)
if ~isscalar(n) || mod(n,1) ~= 0 || n < 1
    set(handles.eN, 'BackgroundColor', [0.86 0.21 0.22]);
    set(handles.eN, 'ForegroundColor', 'white');
    errordlg(['Valor de N invalido!'],'Parâmetro Invalido','modal');
    return;
else
    set(handles.eN, 'BackgroundColor', 'white');
    set(handles.eN, 'ForegroundColor', 'black');
end

% obter e validar o valor inicial da funcao.
strY0 = get(handles.eY0,'String');
Y0 = str2num(strY0);
if ~isscalar(Y0)
    set(handles.eY0, 'BackgroundColor', [0.86 0.21 0.22]);
    set(handles.eY0, 'ForegroundColor', 'white');
    errordlg(['Valor de Y0 inválido!'],'Parâmetro Inválido','modal');
    return;
else
    set(handles.eY0, 'BackgroundColor', 'white');
    set(handles.eY0, 'ForegroundColor', 'black');
end


    escolha = find([handles.rEuler ...
                    handles.rEulerM ...
                    handles.rRK2 ...
                    handles.rRK4 ...
                    handles.rODE45 ...
                    handles.rADAMS ...
                    handles.rTodos] == get(handles.bSelect,'SelectedObject'));
    EULER  = 1;
    EULERM = 2;
    RK2    = 3;
    RK4    = 4;
    ODE45  = 5;
    ADAMS  = 6;
    TODOS  = 7;

try 
    yEuler  = N_Euler(f,a,b,n,Y0); 
    yEulerM = N_Euler_v2(f,a,b,n,Y0); 
    yRK2    = N_RK2(f,a,b,n,Y0); 
    yRK4    = N_RK4(f,a,b,n,Y0); 
    yODE45  = N_ODE45(f,a,b,n,Y0)';                                 
    yADAMS  = N_Adams(f,a,b,n,Y0);  
    
    t = a:(b-a)/n:b; % discretizacao do dominio
    
    sExacta = dsolve(['Dy=' fs],['y(' num2str(t(1)) ')=' strY0]); % calcular solucao exata
    yExacta = eval(vectorize(char(sExacta)));
    
    switch(escolha)
        case EULER
            plot(t,yEuler,'-r')
            hold on
            plot(t,yExacta,'--b')
            legend('Euler','Exacta')
            
            set(handles.uiTabela,'ColumnName',[{'t'},{'Exacta'},...
                {'Euler'},{'Erro Euler'}])
            
            cTabela = [t.',yExacta.', yEuler.',abs(yEuler-yExacta).'];
            set(handles.uiTabela,'Data',num2cell(cTabela))
            
            
        case EULERM
            plot(t,yEulerM,'-c')
            hold on
            plot(t,yExacta,'--b')
            legend('Euler V2','Exacta')
            
            set(handles.uiTabela,'ColumnName',[{'t'},{'Exacta'},...
                {'Euler V2'},{'Erro Euler V2'}])
            
            cTabela = [t.',yExacta.', yEulerM.',abs(yEulerM-yExacta).'];
            set(handles.uiTabela,'Data',num2cell(cTabela))
            
            
        case RK2
            plot(t,yRK2,'-g')
            hold on
            plot(t,yExacta,'--b')
            legend('RK2','Exacta')
            
            set(handles.uiTabela,'ColumnName',[{'t'},{'Exacta'},...
                {'RK2'},{'Erro RK2'}])
            
            cTabela = [t.',yExacta.', yRK2.',abs(yRK2-yExacta).'];
            set(handles.uiTabela,'Data',num2cell(cTabela))
            
            
        case RK4
            plot(t,yRK4,'-k')
            hold on
            plot(t,yExacta,'--b')
            legend('RK4','Exacta')
            
            set(handles.uiTabela,'ColumnName',[{'t'},{'Exacta'},...
                {'RK4'},{'Erro RK4'}])
            
            cTabela = [t.',yExacta.', yRK4.',abs(yRK4-yExacta).'];
            set(handles.uiTabela,'Data',num2cell(cTabela))
            
            
        case ODE45
            plot(t,yODE45,'-m')
            hold on
            plot(t,yExacta,'--b')
            legend('ODE45','Exacta')
            
            set(handles.uiTabela,'ColumnName',[{'t'},{'Exacta'},...
                {'ODE45'},{'Erro ODE45'}])
            
            cTabela = [t.',yExacta.', yODE45.',abs(yODE45-yExacta).'];
            set(handles.uiTabela,'Data',num2cell(cTabela))
            
         case ADAMS
            plot(t,yADAMS,'-y')
            hold on
            plot(t,yExacta,'--b')
            legend('Adams','Exacta')
            
            set(handles.uiTabela,'ColumnName',[{'t'},{'Exacta'},...
                {'Adams'},{'Erro Adams'}])
            
            cTabela = [t.',yExacta.', yADAMS.',abs(yADAMS-yExacta).'];
            set(handles.uiTabela,'Data',num2cell(cTabela))
            
        case TODOS
            plot(t,yEuler,'-r')
            hold on
            plot(t,yExacta,'-g')
            plot(t,yEulerM,'-k')
            plot(t,yRK2,'-b')
            plot(t,yRK4,'-m')
            plot(t,yODE45,'-y')
            plot(t,yADAMS,'-c')
            legend('Exacta','Euler','Euler V2','RK2','RK4','ODE45','Adams')
            
            set(handles.uiTabela,'ColumnName',[{'t'},{'Exacta'},...
                {'Euler'},{'Euler V2'},{'RK2'},{'RK4'},{'ODE45'},...
                {'Adams'},{'Erro Euler'},{'Erro Euler V2'},{'Erro RK2'},...
                {'Erro RK4'},{'Erro ODE45'},{'Erro Adams'}])
            
            cTabela = [t.',yExacta.', yEuler.',yEulerM.',yRK2.',yRK4.',yODE45.',yADAMS.',...
                abs(yEuler-yExacta).',abs(yEulerM-yExacta).',...
                abs(yRK2-yExacta).',abs(yRK4-yExacta).',abs(yODE45-yExacta).',...
                abs(yADAMS-yExacta).'];
            set(handles.uiTabela,'Data',num2cell(cTabela))
            
    end
    grid on 
    xlabel('Eixo dos XX')
    ylabel('Eixo dos YY')
    hold off 
    
catch Me
     errordlg(['Ocorreu um Erro: ' Me.message],'Erro','modal');
end % try escolha
% termina funcao: Actualiza

% --- Executes on button press in pbSaveExcel.
function pbSaveExcel_Callback(hObject, eventdata, handles)
% hObject    handle to pbSaveExcel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Obter o caminho para o ficheiro onde ira ficar guardado os dados da
% tabela 

[arq,dir] = uiputfile('*.xls','Guardar Tabela'); 

% Caso o utilizador tenha cancelado a interface de dialogo
if isequal(arq,0) 
    return
end

% Obter os dados na Tabela
dados = get(handles.uiTabela, 'Data');

% Obter os nomes das colunas 
col_name = get(handles.uiTabela, 'ColumnName');

%Vector passado para o excel
tbl = [col_name'; dados];

% Guardar o vector no excel.
xlswrite(fullfile(dir, arq), tbl);

% --- Executes on button press in pbSaveJpg.
function pbSaveJpg_Callback(hObject, eventdata, handles)
% hObject    handle to pbSaveJpg (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Obter o caminho para o ficheiro onde ira ficar guardado a imagem do
% grafico

[arq,dir] = uiputfile('*.jpg','Guardar Grafico'); 

if isequal(arq,0) 
    %Caso o utilizador tenha cancelado a interface de dialogo
    return
end

% Criar um frame na zona dos graficos
F = getframe(handles.axes1, [-30, -30 , 830, 450]);

% Passar o frame para uma imagem
x = frame2im(F);

% Guardar a imagem no ficheiro obtido com o (uiputfile);
imwrite(x,fullfile(dir, arq));


% --- Executes when figure1 is resized.
function figure1_SizeChangedFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --- Executes on button press in rEulerM.
function rEulerM_Callback(hObject, eventdata, handles)
% hObject    handle to rEulerM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rEulerM

% --- Executes on button press in rODE45.
function rODE45_Callback(hObject, eventdata, handles)
% hObject    handle to rODE45 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rODE45

% --------------------------------------------------------------------
function bSelect_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to bSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --- Executes during object creation, after setting all properties.
function bSelect_CreateFcn(hObject, eventdata, handles)
% hObject    handle to bSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% --- Executes during object deletion, before destroying properties.
function bSelect_DeleteFcn(hObject, eventdata, handles)
% hObject    handle to bSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --- Executes when bSelect is resized.
function bSelect_ResizeFcn(hObject, eventdata, handles)
% hObject    handle to bSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in rADAMS.
function rADAMS_Callback(hObject, eventdata, handles)
% hObject    handle to rADAMS (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rADAMS


% --- Executes on button press in rEuler.
function rEuler_Callback(hObject, eventdata, handles)
% hObject    handle to rEuler (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rEuler


% --- Executes on button press in rTodos.
function rTodos_Callback(hObject, eventdata, handles)
% hObject    handle to rTodos (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rTodos


% --- Executes when user attempts to close figure1.
function figure1_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: delete(hObject) closes the figure
delete(hObject);
