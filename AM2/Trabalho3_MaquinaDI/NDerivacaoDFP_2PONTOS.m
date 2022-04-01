%   Licenciatura Engenharia Informática - Pós Laboral
%   Matlab .: Atividade03Trabalho - Máquina para Derivação e Integração
%   Professor Disciplina: Arménio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020
%
%   Derivação Numérica
%   Formúla das Diferenças progressivas
%
%   f'(xi)=(f(x(i+1))-f(x(i))/h
%   INPUT:  
%         f - função
%         [a, b] - intervalo de derivação
%         h - passo da discretização
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