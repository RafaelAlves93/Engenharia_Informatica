import numpy as np

R1=2000
R4=2000
R2=1000
R3=1000
I1=1/1000
V1=1

A=np.array([[R1+R4,-R4,-1],[-R4,R2+R3+R4,0],[1,0,0]])
b=np.array([-V1,V1,I1])

solucao=np.linalg.solve(A,b)

print('IA (mA) = ',solucao[0]*10**3)
print('IB (mA) = ',solucao[1]*10**3)
print('VI1 (V) = ',solucao[2])
