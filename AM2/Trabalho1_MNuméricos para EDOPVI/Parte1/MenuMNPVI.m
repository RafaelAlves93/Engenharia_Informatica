%MENUMNPVI  Menu de Métodos Numéricos para um PVI
%   y = MenuMNPVI(f,a,b,n,y0)
%   y'= f(t,y) com t=[a, b] e y(a)=y0 condição inicial  
%
%INPUT:
%   f - função do 2.º membro da Equação Diferencial
%   [a, b] - extremos do intervalo da variável independente t
%   n - número de subintervalos ou iterações do método
%   y0 - condição inicial t=a -> y=y0
%OUTPUT: 
%   y - vector das soluções aproximações
%
%   12/03/2020 - ArménioCorreia .: armenioc@isec.pt 

function y=MenuMNPVI(f,a,b,n,y0)
              strF=input('\n f(t,y) = ','s');
              f=@(t,y) eval(vectorize(strF));
              a=str2num(input('a = ','s'));
              b=str2num(input('b = ','s'));
              n=str2num(input('n = ','s'));
              y0=str2num(input('y0 = ','s'));
y=[];
menuMNPVI = 1;
while menuMNPVI~=8
    clc
    disp('--------------------------------------------------')
    disp('           Métodos Numéricos para PVI             ')
    disp('--------------------------------------------------')
    menuMNPVI=menu('Métodos Numéricos para PVI', ...
                   'Método de Euler',...
                   'Método de Euler Melhorado',...
                   'Método RK2',...
                   'Método RK4',...
                   'Método ODE45',...
                   'Método ADAMS',...
                   'Todos',...
                   'Saír');
    switch menuMNPVI 
        case 1
              y = NEuler(f,a,b,n,y0);
        case 2  
              y = Euler_melhorado(f,a,b,n,y0);                          
        case 3
              y = RK2(f,a,b,n,y0);                        
        case 4
              y = RK4(f,a,b,n,y0);   
        case 5
              y = ODE45(f,a,b,n,y0);
        case 6
              y = Adams(f,a,b,n,y0);
        case 7
              y = [NEuler(f,a,b,n,y0);
              Euler_melhorado(f,a,b,n,y0);
              RK2(f,a,b,n,y0);
              RK4(f,a,b,n,y0); 
              ODE45(f,a,b,n,y0)';
              Adams(f,a,b,n,y0);]; 
        case 8
            return;
    end
    
    disp('-----------Solução aproximada do PVI---------')
    disp(y)
    input('Prima numa tecla para continuar »')
end
            