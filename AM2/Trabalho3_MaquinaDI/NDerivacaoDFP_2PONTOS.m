%   Licenciatura Engenharia Inform�tica - P�s Laboral
%   Matlab .: Atividade03Trabalho - M�quina para Deriva��o e Integra��o
%   Professor Disciplina: Arm�nio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020
%
%   Deriva��o Num�rica
%   Form�la das Diferen�as progressivas
%
%   f'(xi)=(f(x(i+1))-f(x(i))/h
%   INPUT:  
%         f - fun��o
%         [a, b] - intervalo de deriva��o
%         h - passo da discretiza��o
%         y - imagens x vs y
%   OUTPUT: 
%         [x, y] - malha de pontos
%         dydx - derivada de f 

function [x,y,dydx]=NDerivacaoDFP_2PONTOS(f,a,b,h,y)
x=a:h:b;
n=length(x);
if nargin==4
    y=f(x);
end;
dydx=zeros(1,n);
for i=1:n-1
    dydx(i)=(y(i+1)-y(i))/h;
end;
dydx(n)=(y(n)-y(n-1))/h;