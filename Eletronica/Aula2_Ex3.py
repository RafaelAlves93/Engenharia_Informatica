# FOLHA EXERCICIOS - AULA 2

# 3.a)
# 1º calcular Req (R1, R2 e R3 em serie)
R1=500
R2=2500
R3=1000
Req=(R1+R2+R3)/1000
print('\nReq = R1+R2+R3 =',Req,'KOhm')

# 2º aplicar a lei de Ohm (V=R*I)
V1=2
I=V1/Req
print('3.a) \nCorrente igual nas 3 resistencias -> I=',I,'mA')

# 3.b)
# calcular a tensao em R3
# usando Lei de Ohm -> VR3=R3*I
VR3=R3*I
print('3.b) \nTensao em R3 -> VR3 =',VR3,'V')

# 3.c)
# calcular a tensao em R1
# usando divisor de tensao -> VR1=(R1/(R1+R2+R3))*V1
VR1=R1*V1/(R1+R2+R3)
print('3.c) \nTensao em R1 -> VR1 =',VR1,'V')
