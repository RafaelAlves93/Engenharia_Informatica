%   Licenciatura Engenharia Inform�tica - P�s Laboral
%   Matlab .: Atividade03Trabalho - M�quina para Deriva��o e Integra��o
%   Professor Disciplina: Arm�nio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020

%   Deriva��o Num�rica - f�rmula das diferen�as centradas
%   Form�la das Diferen�as Centradas
% 
%   f'(xi)=(f(x(i+1))-f(x(i-1)))/(2*h)
%   INPUT:  
%        f - fun��o
%        [a, b] - intervalo de deriva��o
%        h - passo da discretiza��o
%        y - imagens x vs y
%   OUTPUT: 
%        [x, y] - malha de pontos
%        dydx - derivada de f 

function [x,y,dydx]=NDerivacaoDFCENT(f,a,b,h,y)
x=a:h:b;
n=length(x);
if nargin==4
    y=f(x);
end;
dydx=zeros(1,n);
dydx(1)=(y(3)-y(2))/h;
for i=2:n-1
    dydx(i)=(y(i+1)-y(i-1))/(2*h);
end;
dydx(n)=(y(n-2)-y(n-1))/h;
