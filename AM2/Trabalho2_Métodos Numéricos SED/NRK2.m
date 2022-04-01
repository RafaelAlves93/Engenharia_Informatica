%   Licenciatura Engenharia Informática - Pós Laboral
%   Matlab .: Atividade03Trabalho - Máquina para Derivação e Integração
%   Professor Disciplina: Arménio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020
% NRK2  Método de Runge-Kutta de ordem 2 para SED.
%   [t,u,v] = NRK2(f,g,a,b,n,u0,vo) 
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
%   y(i+1) = y(i)+h*f(t(i),y(i)) , i =0,1,...,n-1

function [t,u,v]=NRK2(f,g,a,b,n,u0,v0)
h = (b-a)/n;                                                        
t = a:h:b;                                                          
u = zeros(1,n+1);                                                   
v = zeros(1,n+1);                                                   
u(1) = u0;                                                          
v(1) = v0;  
for i=1:n
    k1u=h*f(t(i),u(i),v(i));
    k1v=h*g(t(i),u(i),v(i));
    k2u=h*f(t(i+1),u(i)+k1u,v(i)+k1u);  
    k2v=h*g(t(i+1),u(i)+k1v,v(i)+k1v);
    u(i+1)=u(i)+(k1u+k2u)/2;
    v(i+1)=v(i)+(k1v+k2v)/2;
end