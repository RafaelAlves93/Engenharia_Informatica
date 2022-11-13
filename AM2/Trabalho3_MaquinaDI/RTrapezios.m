%   Licenciatura Engenharia Inform�tica - P�s Laboral
%   Matlab .: Atividade03Trabalho - M�quina para Deriva��o e Integra��o
%   Professor Disciplina: Arm�nio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020
%
%   Aplicar a regra dos Trap�zios
%   T=RTrapezios(f,a,b,n)
%   T=h*(f(a)+2*s+f(b))/2; 
%
%INPUT:
%   f - fun��o
%   a - limite esquerdo do intervalo de c�lculo da �rea
%   b - limite direito do intervalo de c�lculo da �rea
%   n - n�mero de sub-intervalos
%OUTPUT: 
%   T - Aproxima��o do valor da �rea pela Regra dos Trap�zios

function T=RTrapezios(f,a,b,n)
h=(b-a)/n;
x=a;
s=0;
for i=1:n-1
    x=x+h;
    s=s+f(x);
end
T=h*(f(a)+2*s+f(b))/2;