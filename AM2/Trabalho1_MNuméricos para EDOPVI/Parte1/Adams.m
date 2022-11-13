%Licenciatura Engenharia Informática - Pós Laboral
%Matlab .: Atividade01Trabalho » MNuméricos para EDO/PVI
%Professor Disciplina: Arménio Correia
%Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%Data: 13/04/2020


function y = Adams(f,a,b,n,y0)
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
    
        for j=4:n
            G1=f(t(j),y(j));
            G2=f(t(j-1),y(j-1));
            G3=f(t(j-2),y(j-2));
            G4=f(t(j-3),y(j-3));
            
% funcao do preditor         
            y(j+1)= y(j)+(h*(55*G1-59*G2+37*G3-9*G4)/24);
         
% funcao do corretor
            y(j+1)=y(j)+(h*(9*f(t(j+1),y(j+1))+19*G1-5*G2+G3)/24);
           
        end
 end    