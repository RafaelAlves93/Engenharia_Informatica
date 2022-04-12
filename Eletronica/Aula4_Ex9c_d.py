import numpy as np

R1=4000
R2=6000
R3=10000
R4=10000
I1=5/1000
V1=5

A=np.array([[1/R1+1/R2,-1/R2,0],[1/R2,-1/R2-1/R4-1/R3,0],[1/R1,1/R3,-1]])
b=np.array([I1+V1/R1,-V1/R3,V1*(1/R3+1/R1)])


solucao=np.linalg.solve(A,b)

print('VA (V) = ',solucao[0])
print('VB (V) = ',solucao[1])
print('IF (mA) = ',solucao[2]*1000)
VA=solucao[0]
VB=solucao[1]
VC=V1
IA = -I1
IB = (VA-VC)/R1
IC = (VA-VB)/R2
ID = VB/R4
IE = (VB-VC)/R3

print('IA (mA) = ',IA*1000)
print('IB (mA) = ',IB*1000)
print('IC (mA) = ',IC*1000)
print('ID (mA) = ',ID*1000)
print('IE (mA) = ',IE*1000)

# d)

# OS VALORES DAS CORRENTES DO MÉTODO DAS TENSÕES NODAIS
IF = IB+IE
P_P=R1*(IB)**2+R3*(IE)**2+R2*(IC)**2+R4*(ID)**2+abs(V1*IF)
P_F=VA*IA

print('Potencia de perdas = ',P_P)
print('Potencia fornecida = ',P_F)

