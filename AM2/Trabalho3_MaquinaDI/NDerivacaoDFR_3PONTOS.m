%   Licenciatura Engenharia Informática - Pós Laboral
%   Matlab .: Atividade03Trabalho - Máquina para Derivação e Integração
%   Professor Disciplina: Arménio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020
%
%   Derivação Numéricas 
%   Formúla das Diferenças Regressivas (em 3 pontos)
%
%   f'(xi)=(f(x(i-2))-4*f(x(i-1))+3*f(x(i)))/h
%   INPUT:  
%        f - função
%        [a, b] - intervalo de derivação
%        h - passo da discretização
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