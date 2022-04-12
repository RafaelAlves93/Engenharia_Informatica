# FOLHA EXERCICIOS - AULA 2

# 4
I1=1/1000
R1=1000
R2=1000
R3=8000
R4=8000
# alinea a)
print('Pergunta 4 alinea a)')
print('Corrente em R1 = ',I1,'A')
print('\n')


# alinea b)
# 1º simplificar o circuito
# calcular paralelo de R2//R3//R4 -> Req1 = R2//R3//R4
print('Pergunta 4 alinea b)')
Req1=pow((1/R2+1/R3+1/R4),-1)
print('Resistencia equivalente 1 (Ohms) = ',Req1)
VR4=I1*Req1
print('Tensao na resistencia R4 (V) = ',VR4)
print('\n')


# alinea c)
# 1º simplificar o circuito (Calcular paralelo R3//R4)
print('Pergunta 4 alinea c)')
Req2=pow((1/R3+1/R4),-1)
print('Resistencia equivalente 2 (Ohms) = ',Req2)
# 2º utilizar formula do divisor de corrente
IR2=Req2*I1/(Req2+R2)
print('Corrente na Resistencia 2 (A) = ',IR2)
print('Corrente na Resistencia 2 (mA) = ',IR2*1000)
print('Corrente na Resistencia 2 (uA) = ',IR2*1000000)
