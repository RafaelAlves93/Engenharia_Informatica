%   Licenciatura Engenharia Informática - Pós Laboral
%   Matlab .: Atividade03Trabalho - Máquina para Derivação e Integração
%   Professor Disciplina: Arménio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020
%
%   Aplicar a regra dos Trapézios
%   T=RTrapezios(f,a,b,n)
%   T=h*(f(a)+2*s+f(b))/2; 
%
%INPUT:
%   f - função
%   a - limite esquerdo do intervalo de cálculo da área
%   b - limite direito do intervalo de cálculo da área
%   n - número de sub-intervalos
%OUTPUT: 
%   T - Aproximação do valor da área pela Regra dos Trapézios

function T=RTrapezios(f,a,b,n)
h=(b-a)/n;
x=a;
s=0;
for i=1:n-1
    x=x+h;
    s=s+f(x);
end
T=h*(f(a)+2*s+f(b))/2;