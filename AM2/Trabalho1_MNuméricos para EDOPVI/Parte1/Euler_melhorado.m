%Licenciatura Engenharia Informática - Pós Laboral
%Matlab .: Atividade01Trabalho » MNuméricos para EDO/PVI
%Professor Disciplina: Arménio Correia
%Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%Data: 13/04/2020


function y=Euler_melhorado(f,a,b,n,y0)
h=(b-a)/n;
t=a:h:b;
y=zeros(1,n+1);
y(1)=y0;
for i=1:n
    k1=h*f(t(i),y(i));
    k2=h*f(t(i+1),y(i)+k1);
    y(i+1)=y(i)+(k1+k2)/2;
end
