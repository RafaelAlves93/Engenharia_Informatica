%   Licenciatura Engenharia Informática - Pós Laboral
%   Matlab .: Atividade03Trabalho - Máquina para Derivação e Integração
%   Professor Disciplina: Arménio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020
%
%   Aplicar a Regra de Simpson
%   out_S=RSimpson(f,a,b,n)
%   out_S=h*(f(a)+s+f(b))/3;
%
%INPUT:
%   f - função
%   a - limite esquerdo do intervalo de cálculo da área
%   b - limite direito do intervalo de cálculo da área
%   n - número de sub-intervalos
%OUTPUT: 
%   S - Aproximação do valor da área pela Regra de Simpson

function out_S=RSimpson(f,a,b,n)
h=(b-a)/n;
x=a;
s=0;
for i=1:n-1,
    x=x+h;
    if mod(i,2)==0
        s=s+2*f(x);
    else
        s=s+4*f(x);
    end
end
out_S=h*(f(a)+s+f(b))/3;
