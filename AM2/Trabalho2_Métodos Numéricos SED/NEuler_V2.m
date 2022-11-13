%   Licenciatura Engenharia Informática - Pós Laboral
%   Matlab .: Atividade03Trabalho - Máquina para Derivação e Integração
%   Professor Disciplina: Arménio Correia
%   Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%   Data: 06/06/2020
% NEULER_M  Método de Euler Melhorado para SED
%   [t,u,v] = NEuler_M(f,g,a,b,n,u0,vo) 
%   u'= f(t,u,v), v'=g(t,u,v), t=[a, b], u(a)=u0 e v(a)=v0 
%
% INPUT:
%   f - função do 2o membro da Equacao Diferencial
%   [a, b] - extremos do intervalo da variável independente t
%   n - número de subintervalos ou iterações do método
%   y0 - condição inicial t=a -> y=y0
%
% OUTPUT: 
%   [t,u,v] - vector das soluções aproximações e da discretização de t
%   u(i+1) = u(i)+h*f(t(i),u(i),v(i))
%   v(i+1) = v(i)+h*g(t(i),u(i),v(i)) , i =0,1,...,n-1

function [t,u,v] = NEuler_V2(f,g,a,b,n,u0,v0)
h = (b-a)/n;                                                        
t = a:h:b;                                                          
u = zeros(1,n+1);                                                   
v = zeros(1,n+1);                                                   
u(1) = u0;                                                          
v(1) = v0;                                                         
for i=1:n
    u(i+1)=u(i)+h*f(t(i),u(i),v(i));                                
    v(i+1)=v(i)+h*g(t(i),u(i),v(i));                               
    u(i+1)=u(i)+(h/2)*(f(t(i),u(i),v(i))+f(t(i+1),u(i+1),v(i+1)));  
    v(i+1)=v(i)+(h/2)*(g(t(i),u(i),v(i))+g(t(i+1),u(i+1),v(i+1)));  
end
