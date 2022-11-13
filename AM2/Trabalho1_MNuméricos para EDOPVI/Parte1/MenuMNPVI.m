%MENUMNPVI  Menu de M�todos Num�ricos para um PVI
%   y = MenuMNPVI(f,a,b,n,y0)
%   y'= f(t,y) com t=[a, b] e y(a)=y0 condi��o inicial  
%
%INPUT:
%   f - fun��o do 2.� membro da Equa��o Diferencial
%   [a, b] - extremos do intervalo da vari�vel independente t
%   n - n�mero de subintervalos ou itera��es do m�todo
%   y0 - condi��o inicial t=a -> y=y0
%OUTPUT: 
%   y - vector das solu��es aproxima��es
%
%   12/03/2020 - Arm�nioCorreia .: armenioc@isec.pt 

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
    disp('           M�todos Num�ricos para PVI             ')
    disp('--------------------------------------------------')
    menuMNPVI=menu('M�todos Num�ricos para PVI', ...
                   'M�todo de Euler',...
                   'M�todo de Euler Melhorado',...
                   'M�todo RK2',...
                   'M�todo RK4',...
                   'M�todo ODE45',...
                   'M�todo ADAMS',...
                   'Todos',...
                   'Sa�r');
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
    
    disp('-----------Solu��o aproximada do PVI---------')
    disp(y)
    input('Prima numa tecla para continuar �')
end
            