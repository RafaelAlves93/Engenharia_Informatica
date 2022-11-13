%   Licenciatura Engenharia Informática - Pós Laboral
%   Matlab .: Atividade03Trabalho - Máquina para Derivação e Integração
%   Professor Disciplina: Arménio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020

%   23/03/2020 - ArménioCorreia .: armenioc@isec.pt

function varargout = MaquinaMNSED(varargin)
% MaquinaMNSED M-file for MaquinaMNSED.fig
%      MaquinaMNSED, by itself, creates a new MaquinaMNSED or raises the existing
%      singleton*.
%
%      H = MaquinaMNSED returns the handle to a new MaquinaMNSED or the handle to
%      the existing singleton*.
%
%      MaquinaMNSED('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MaquinaMNSED.M with the given input arguments.
%
%      MaquinaMNSED('Property','Value',...) creates a new MaquinaMNSED or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before MaquinaMNPVI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to MaquinaMNPVI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help MaquinaMNSED

% Last Modified by GUIDE v2.5 06-June-2020 19:50:44

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @MaquinaMNSED_OpeningFcn, ...
                   'gui_OutputFcn',  @MaquinaMNSED_OutputFcn, ...
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


% --- Executes just before MaquinaMNSED is made visible.
function MaquinaMNSED_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to MaquinaMNSED (see VARARGIN)

% Choose default command line output for MaquinaMNSED
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);


% UIWAIT makes MaquinaMNSED wait for user response (see UIRESUME)
% uiwait(handles.figureMaquinaMNSED);


% --- Outputs from this function are returned to the command line.
function varargout = MaquinaMNSED_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pbAtualizar.
function pbAtualizar_Callback(hObject, eventdata, handles)
% hObject    handle to pbAtualizar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
MyAtualizar(handles);


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



function eU0_Callback(hObject, eventdata, handles)
% hObject    handle to eU0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eU0 as text
%        str2double(get(hObject,'String')) returns contents of eU0 as a double


% --- Executes during object creation, after setting all properties.
function eU0_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eU0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function eV0_Callback(hObject, eventdata, handles)
% hObject    handle to eV0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eV0 as text
%        str2double(get(hObject,'String')) returns contents of eV0 as a double


% --- Executes during object creation, after setting all properties.
function eV0_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eV0 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function MyAtualizar(handles)
strF=get(handles.eF,'String');
strG=get(handles.eG,'String');
f=@(t,u,v) eval(vectorize(strF));
g=@(t,u,v) eval(vectorize(strG));
a=str2num(get(handles.eA,'String'));
b=str2num(get(handles.eB,'String'));
n=str2num(get(handles.eN,'String'));
u0=str2num(get(handles.eU0,'String'));
v0=str2num(get(handles.eV0,'String'));

escolhabg=get(handles.bgMetodos,'SelectedObject');
escolha=find([handles.rbEuler,...
              handles.rbEulerM,...
              handles.rbRK2,...
              handles.rbRK4,...
              handles.rbTodos]==escolhabg);
          
EULER=1; EULERV2=2; RK2=3; RK4=4; TODOS=5;


FTeste=MException('MATLAB:MyAtualizar:badF','Introduza uma função em t,u e v!');
TesteNRealA=MException('MATLAB:MyAtualizar:badNRA','Introduza um número real!');
TesteNRealB=MException('MATLAB:MyAtualizar:badNRB','Introduza um número real e maior que a!');
TesteNRealN=MException('MATLAB:MyAtualizar:badNRN','Introduza um número real e maior ou igual a 2!');


try
    try
        fT=f(sym('t'),sym('u'),sym('v'));
        set(handles.eF,'BackgroundColor','w');
    catch
        set(handles.eF,'BackgroundColor','r'); 
        throw(FTeste)
    end
    if ~(isscalar(a) && isreal(a))
        set(handles.eA,'BackgroundColor','r'); 
        throw(TesteNRealA)
    else
        set(handles.eA,'BackgroundColor','w');
    end
    if ~(isscalar(b) && isreal(b) && b > a)
        set(handles.eB,'BackgroundColor','r'); 
        throw(TesteNRealB)
    else
        set(handles.eB,'BackgroundColor','w');
    end
    if ~(isscalar(n) && isreal(n) && n>=2)
        set(handles.eN,'BackgroundColor','r'); 
        throw(TesteNRealN)
    else
        set(handles.eN,'BackgroundColor','w');
    end
    if ~(isscalar(u0) && isreal(u0))
        set(handles.eU0,'BackgroundColor','r'); 
        throw(TesteNRealA)
    else
        set(handles.eU0,'BackgroundColor','w');
    end
    if ~(isscalar(v0) && isreal(v0))
        set(handles.eV0,'BackgroundColor','r'); 
        throw(TesteNRealA)
    else
        set(handles.eV0,'BackgroundColor','w');
    end
    
    [t,u,v]= NEuler(f,g,a,b,n,u0,v0)
    uEuler = u;
    [t,u,v] = NEuler_V2(f,g,a,b,n,u0,v0)
    uEulerV2 = u;
    [t,u,v] = NRK2(f,g,a,b,n,u0,v0)
	uRK2 = u;
    [t,u,v] = NRK4(f,g,a,b,n,u0,v0)
    uRK4 = u;

    t=a:(b-a)/n:b;
  
    switch escolha
        case EULER
             plot(t,uEuler,'-r')
             legend('Euler')
             tabela=[t.',uEuler.'];
             set(handles.uiTabela,'Data',num2cell(tabela))
             set(handles.uiTabela,'ColumnName',{'t','Euler'})
        case EULERV2
             plot(t,uEulerV2,'-c')
             legend('EulerV2')
             tabela=[t.',uEulerV2.'];
             set(handles.uiTabela,'Data',num2cell(tabela))
             set(handles.uiTabela,'ColumnName',{'t','EulerV2'})
        case RK2
             plot(t,uRK2,'-g')
             legend('RK2')
             tabela=[t.',uRK2.'];
             set(handles.uiTabela,'Data',num2cell(tabela))
             set(handles.uiTabela,'ColumnName',{'t','RK2'})
        case RK4            
             plot(t,uRK4,'-k')
             legend('RK4')
             tabela=[t.',uRK4.'];
             set(handles.uiTabela,'Data',num2cell(tabela))
             set(handles.uiTabela,'ColumnName',{'t','RK4'})
        case TODOS
             plot(t,uEuler,'-r')
             hold on
             plot(t,uEulerV2,'-c')
             plot(t,uRK2,'-g')
             plot(t,uRK4,'-k')
             legend('Euler','EulerV2','RK2','RK4')
             tabela=[t.',uEuler.',uEulerV2.',uRK2.',uRK4.'];
             set(handles.uiTabela,'Data',num2cell(tabela))
             set(handles.uiTabela,'ColumnName',...
                 {'t','Euler','EulerV2','RK2','RK4'})
             hold off
    end
        % hold off
        grid on
           
catch Me
    errordlg(['Ocorreu um erro. ',Me.message],'ERRO','modal')
end


% --------------------------------------------------------------------
function MFile_Callback(hObject, eventdata, handles)
% hObject    handle to MFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function MSair_Callback(hObject, eventdata, handles)
% hObject    handle to MSair (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
SN=questdlg('Quer mesmo sair?','Sair','Sim','Não','Sim');
if strcmp(SN,'Não')
    return
end
delete(handles.figureMaquinaMNSED)


% --- Executes when user attempts to close figureMaquinaMNSED.
function figureMaquinaMNSED_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figureMaquinaMNSED (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: delete(hObject) closes the figure

MSair_Callback([], [], handles)

% --- Executes on button press in pbReset.
function pbReset_Callback(hObject, eventdata, handles)
% hObject    handle to pbReset (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.eF,'string',num2str(0));
set(handles.eG,'string',num2str(0));
set(handles.eA,'string',num2str(0));
set(handles.eB,'string',num2str(0));
set(handles.eN,'string',num2str(0));
set(handles.eU0,'string',num2str(0));
set(handles.eV0,'string',num2str(0));


% --- Executes on button press in cbTabela.
function cbTabela_Callback(hObject, eventdata, handles)
% hObject    handle to cbTabela (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of cbTabela
if get(hObject,'Value')
    set(handles.uiTabela,'Visible','on');
else
    set(handles.uiTabela,'Visible','off');
end


% --- Executes during object creation, after setting all properties.
function axes1_CreateFcn(hObject, eventdata, ~)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: place code in OpeningFcn to populate axes1


function eG_Callback(hObject, eventdata, handles)
% hObject    handle to eG (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of eG as text
%        str2double(get(hObject,'String')) returns contents of eG as a double


% --- Executes during object creation, after setting all properties.
function eG_CreateFcn(hObject, eventdata, handles)
% hObject    handle to eG (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu2.
function popupmenu2_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu2

escolhap = get(handles.popupmenu2,'Value'); 

    switch escolhap
        case 1
 
        case 2
            set(handles.eF,'string',num2str('v'));
            set(handles.eG,'string',num2str('-sin(u)-0.3*v'));
            set(handles.eA,'string',num2str(0));
            set(handles.eB,'string',num2str(30));
            set(handles.eN,'string',num2str(10));
            set(handles.eU0,'string',num2str('pi/2'));
            set(handles.eV0,'string',num2str(5));
        case 3
            set(handles.eF,'string',num2str('v'));
            set(handles.eG,'string',num2str('-2*v-2*u+4*cos(t)+2*sin(t)'));
            set(handles.eA,'string',num2str(0));
            set(handles.eB,'string',num2str(30));
            set(handles.eN,'string',num2str(10));
            set(handles.eU0,'string',num2str(0));
            set(handles.eV0,'string',num2str(5));
        case 4
            set(handles.eF,'string',num2str('v'));
            set(handles.eG,'string',num2str('-10*v-25*u'));
            set(handles.eA,'string',num2str(0));
            set(handles.eB,'string',num2str(30));
            set(handles.eN,'string',num2str(10));
            set(handles.eU0,'string',num2str(0));
            set(handles.eV0,'string',num2str(-4));
        case 5
            set(handles.eF,'string',num2str('v'));
            set(handles.eG,'string',num2str('Problema não implementado'));
            set(handles.eA,'string',num2str(0));
            set(handles.eB,'string',num2str(0));
            set(handles.eN,'string',num2str(0));
            set(handles.eU0,'string',num2str(0));
            set(handles.eV0,'string',num2str(0));           
        case 6
            set(handles.eF,'string',num2str('v'));
            set(handles.eG,'string',num2str('Problema não implementado'));
            set(handles.eA,'string',num2str(0));
            set(handles.eB,'string',num2str(0));
            set(handles.eN,'string',num2str(0));
            set(handles.eU0,'string',num2str(0));
            set(handles.eV0,'string',num2str(0));                        
    end

% --- Executes during object creation, after setting all properties.
function popupmenu2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
