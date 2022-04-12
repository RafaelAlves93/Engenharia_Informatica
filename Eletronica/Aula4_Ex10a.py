import numpy as np

R1=2000
R4=2000
R2=1000
R3=1000
I1=1/1000
V1=1

#   IA      -IB     -IC         0       = 0
#   IA      0       0           0       = I1
#   R1.IA   R4.IB   0           -VI1    = -V1
#   0       -R4.IB  (R2+R3).IC  0       = V1

A=np.array([[1,-1,-1,0],[1,0,0,0],[R1,R4,0,-1],[0,-R4,(R2+R3),0]])
b=np.array([0,I1,-V1,V1])

solucao=np.linalg.solve(A,b)

print('IA (mA) = ',solucao[0]*10**3)
print('IB (mA) = ',solucao[1]*10**3)
print('IC (mA) = ',solucao[2]*10**3)
print('VI1 (V) = ',solucao[3])
