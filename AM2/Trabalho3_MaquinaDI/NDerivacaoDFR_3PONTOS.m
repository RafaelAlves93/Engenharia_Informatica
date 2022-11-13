%   Licenciatura Engenharia Inform�tica - P�s Laboral
%   Matlab .: Atividade03Trabalho - M�quina para Deriva��o e Integra��o
%   Professor Disciplina: Arm�nio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020
%
%   Deriva��o Num�ricas 
%   Form�la das Diferen�as Regressivas (em 3 pontos)
%
%   f'(xi)=(f(x(i-2))-4*f(x(i-1))+3*f(x(i)))/h
%   INPUT:  
%        f - fun��o
%        [a, b] - intervalo de deriva��o
%        h - passo da discretiza��o
%        y - imagens x vs y
%   OUTPUT: 
%        [x, y] - malha de pontos
%        dydx - derivada de f 

function [x,y,dydx]=NDerivacaoDFR_3PONTOS(f,a,b,h,y)
x=a:h:b;
n=length(x);
if nargin==4
    y=f(x);
end
dydx=zeros(1,n);
dydx(1)=(y(3)-4*y(2)+3*y(1))/(2*h);
dydx(2)=(y(3)-4*y(2)+3*y(1))/(2*h);
for i=3:n
    dydx(i)=(y(i-2)-4*y(i-1)+3*y(i))/(2*h);
end