%Licenciatura Engenharia Inform�tica - P�s Laboral
%Matlab .: Atividade01Trabalho � MNum�ricos para EDO/PVI
%Professor Disciplina: Arm�nio Correia
%Aluno: Rafael Filipe Martins Alves - 2014013189 | a21240485@isec.pt
%Data: 13/04/2020


function y=N_ODE45(f,a,b,n,y0)
	h=(b-a)/n;
	tspan=(a:h:b);
	[t,y]=ode45(f,tspan,y0);
 
%Como nao vamos precisar do valor de t neste caso
%podemos substituir o t pelo ~ fica: 
 
	[~,y]=ode45(f,tspan,y0);