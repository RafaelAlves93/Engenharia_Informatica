%   Licenciatura Engenharia Informática - Pós Laboral
%   Matlab .: Atividade03Trabalho - Máquina para Derivação e Integração
%   Professor Disciplina: Arménio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020
% NRK4  Método de Runge-Kutta de ordem 4 para SED
%   [t,u,v] = NRK4(f,g,a,b,n,u0,vo) 
%   u'= f(t,u,v), v'=g(t,u,v), t=[a, b], u(a)=u0 e v(a)=v0 
%
% INPUT:
%   f - função do 2o membro da Equacao Diferencial
%   [a, b] - extremos do intervalo da variável independente t
%   n - número de subintervalos ou iterações do método
%   y0 - condição inicial t=a -> y=y0
%
% OUTPUT:
%   y - vector das aproximações discretas da solução exata
%   k1=h*(f(t(i), y(i)));
%   k2=h*f(t(i)+ h/2,y(i)+1/2*k1);
%   k3=h*f(t(i)+ h/2,y(i)+1/2*k2);
%   k4=h*f(t(i)+ h,y(i)+k3);
%   y(i+1)=y(i)+(1/6)*(k1+2*k2+2*k3+k4), i =0,1,...,n-1;

function [t,u,v]=NRK4(f,g,a,b,n,u0,v0)
h = (b-a)/n;                                                        
t = a:h:b;                                                          
u = zeros(1,n+1);                                                   
v = zeros(1,n+1);                                                   
u(1) = u0;                                                          
v(1) = v0;
for i=1:n
    k1u=h*f(t(i),u(i),v(i));
    k1v=h*g(t(i),u(i),v(i));
    k2u=h*f(t(i)+ h/2,u(i)+(1/2*k1u),v(i)+(1/2*k1u));    
    k2v=h*g(t(i)+ h/2,u(i)+(1/2*k1v),v(i)+(1/2*k1v)); 
    k3u=h*f(t(i)+ h/2,u(i)+(1/2*k2u),v(i)+(1/2*k2u));   
    k3v=h*g(t(i)+ h/2,u(i)+(1/2*k2v),v(i)+(1/2*k2v)); 
    k4u=h*f(t(i)+ h,u(i)+k3u,v(i)+k3u);   
    k4v=h*g(t(i)+ h,u(i)+k3v,v(i)+k3v);
    u(i+1)=u(i)+(1/6)*(k1u+2*k2u+2*k3u+k4u);  
    v(i+1)=v(i)+(1/6)*(k1v+2*k2v+2*k3v+k4v);
end
