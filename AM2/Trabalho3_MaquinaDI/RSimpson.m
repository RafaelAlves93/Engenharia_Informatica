%   Licenciatura Engenharia Inform�tica - P�s Laboral
%   Matlab .: Atividade03Trabalho - M�quina para Deriva��o e Integra��o
%   Professor Disciplina: Arm�nio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020
%
%   Aplicar a Regra de Simpson
%   out_S=RSimpson(f,a,b,n)
%   out_S=h*(f(a)+s+f(b))/3;
%
%INPUT:
%   f - fun��o
%   a - limite esquerdo do intervalo de c�lculo da �rea
%   b - limite direito do intervalo de c�lculo da �rea
%   n - n�mero de sub-intervalos
%OUTPUT: 
%   S - Aproxima��o do valor da �rea pela Regra de Simpson

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
