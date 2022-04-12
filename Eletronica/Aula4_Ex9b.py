import numpy as np

R1=4000
R2=6000
R3=10000
R4=10000
I1=5/1000
V1=5

A=np.array([[R1+R3+R2,-R2,-R3],[0,1,0],[-R3,-R4,R3+R4]])
b=np.array([0,I1,-V1])

solucao=np.linalg.solve(A,b)

print('IA (mA) = ',solucao[0]*1000)
print('IB (mA) = ',solucao[1]*1000)
print('IC (mA) = ',solucao[2]*1000)
