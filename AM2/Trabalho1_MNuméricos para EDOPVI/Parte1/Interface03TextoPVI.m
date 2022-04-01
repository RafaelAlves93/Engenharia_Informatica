% Interface (versão03) para os PVI
% Aplicação dos Métodos Numéricos de Euler e de Runge-Kutta
% Autor: Arménio Correia  | armenioc@isec.pt
% Data : 12/03/2020

clear
primeiraVez=1;
opcao=1;
while opcao ~= 9
    clc
    disp('------- MÉTODOS NUMÉRICOS PARA PVI ------')
    disp(' ')
    if(~primeiraVez)
        fprintf('1. INTRODUZIR PARÂMETROS DO PVI\n')     
        fprintf('2. MÉTODO DE EULER\n')
        fprintf('3. MÉTODO DE EULER MELHORADO\n')  
        fprintf('4. MÉTODO DE RK2\n')
        fprintf('5. MÉTODO DE RK4\n')
        fprintf('6. MÉTODO ODE45\n')
        fprintf('7. MÉTODO ADAMS\n')
        fprintf('8. APLICAR TODOS OS MÉTODOS EM SIMULTÂNEO\n')
        fprintf('9. TERMINAR\n\n')
        opcao=input('Opção: ');
    else
        opcao=1;
        primeiraVez=0;
    end
    
  y=[];
    switch opcao
        case 1
              strF=input('\n f(t,y) = ','s');
              f=@(t,y) eval(vectorize(strF));
              a=str2num(input('a = ','s'));
              b=str2num(input('b = ','s'));
              n=str2num(input('n = ','s'));
              y0=str2num(input('y0 = ','s'));
        case 2 
              y = NEuler(f,a,b,n,y0);                        
        case 3  
              y = Euler_melhorado(f,a,b,n,y0);                
        case 4
              y = RK2(f,a,b,n,y0);           
        case 5
              y = RK4(f,a,b,n,y0);   
        case 6
              y = ODE45(f,a,b,n,y0);  
        case 7
              y = Adams(f,a,b,n,y0);
        case 8
              y = [NEuler(f,a,b,n,y0);
              Euler_melhorado(f,a,b,n,y0);
              RK2(f,a,b,n,y0);
              RK4(f,a,b,n,y0); 
              ODE45(f,a,b,n,y0)';
              Adams(f,a,b,n,y0);]; 
        case 9
              return;
    end
    
    if ~isempty(y)
        disp(' ')
        disp('------ AS APROXIMAÇÕES OBTIDAS SÃO: ------')
        disp(' ')
        disp(y)
    end
    if opcao~=9
       tecla =input('\nPrima uma tecla para continuar ...');
    end
end   
