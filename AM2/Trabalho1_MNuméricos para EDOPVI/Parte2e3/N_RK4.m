%Licenciatura Engenharia Informática - Pós Laboral
%Matlab .: Atividade01Trabalho » MNuméricos para EDO/PVI
%Professor Disciplina: Arménio Correia
%Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%Data: 13/04/2020


function y = N_RK4(f,a,b,n,y0)
h=(b-a)/n;
t=a:h:b;
y=zeros(1,n+1);
y(1)=y0;
for i=1:n
    k1=h*(f(t(i), y(i)));
    k2=h*f(t(i)+ h/2,y(i)+(1/2*k1));
    k3=h*f(t(i)+ h/2,y(i)+(1/2*k2));
    k4=h*f(t(i)+ h,y(i)+k3);
    y(i+1)=y(i)+(1/6)*(k1+2*k2+2*k3+k4);
end
