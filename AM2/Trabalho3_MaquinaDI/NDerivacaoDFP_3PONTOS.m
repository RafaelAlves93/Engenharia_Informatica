%   Licenciatura Engenharia Informática - Pós Laboral
%   Matlab .: Atividade03Trabalho - Máquina para Derivação e Integração
%   Professor Disciplina: Arménio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020
%
%   Derivação Numérica 
%   Formúla das Diferenças progressivas (em 3 pontos)
%
%   f'(xi)=(-3*(f(x(i))+4*f(x(i+1))-f(x(i+2)))/(2*h)
%   INPUT:  
%         f - função
%         [a, b] - intervalo de derivação
%         h - passo da discretização
%         y - imagens x vs y
%   OUTPUT: 
%         [x, y] - malha de pontos
%         dydx - derivada de f 

function [x,y,dydx]=NDerivacaoDFP_3PONTOS(f,a,b,h,y)
x=a:h:b;
n=length(x);
if nargin==4
    y=f(x);
end;
dydx=zeros(1,n);
for i=1:n-2
    dydx(i)=(-3*y(i)+4*y(i+1)-y(i+2))/(2*h);
end
dydx(n-1)=(-3*y(n-2)+4*y(n-1)-y(n))/(2*h);
dydx(n)=(-3*y(n-2)+4*y(n-1)-y(n))/(2*h);