%   Licenciatura Engenharia Informática - Pós Laboral
%   Matlab .: Atividade03Trabalho - Máquina para Derivação e Integração
%   Professor Disciplina: Arménio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020

%   Derivação Numérica - fórmula das diferenças centradas
%   Formúla das Diferenças Centradas
% 
%   f'(xi)=(f(x(i+1))-f(x(i-1)))/(2*h)
%   INPUT:  
%        f - função
%        [a, b] - intervalo de derivação
%        h - passo da discretização
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
