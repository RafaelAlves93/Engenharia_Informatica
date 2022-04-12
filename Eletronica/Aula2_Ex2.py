# FOLHA EXERCICIOS - AULA 2

# 2.c)

# 1º calcular serie de R5 com R6
R5=2000
R6=1000
Req1=R5+R6
print('R5 em serie com R6 -> Req1=',Req1)

# 2º calcular paralelo em R1 com R2
R2=1000
R1=1000
# Rparalelo = (1/R2 + 1/R6)^-1
Req2=pow((1/R2+1/R1),-1)
print('R1 em paralelo com R2 -> Req2 =',Req2)

# 3º calcular serie de R3 com Req2
R3=2500
Req3 = Req2+R3
print('R3 em serie com Req2 -> Req3 =',Req3)

#4º resistencia final -Paralelo das resistencias Req3,R4 e Req1
R4=3000;
Rfinal =pow((1/Req3+1/R4+1/Req1),-1)
print('Resistencia equivalente final -> Req =',Rfinal)


