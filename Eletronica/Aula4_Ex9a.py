import numpy as np

R1=4000
R2=6000
R3=10000
R4=10000
I1=5/1000
V1=5

#   IA      IB      IC      ID      IE      IF      VI1

#   -IA     IB      -IC     0       0       0       0       = 0
#   0       0       IC      ID      -IE     0       0       = 0
#   0       -IB     0       0       IE      -IF     0       = 0
#   0       -R1.IB  -R2.IC  0       -R3.IE  0       0       = 0
#   0       0       R2.IC   -R4.ID  0       0       -VI1    = 0
#   0       0       0       R4.ID   R3.IE   0       0       = -V1
#   IA      0       0       0       0       0       0       = -I1

A=np.array([[-1,1,-1,0,0,0,0],[0,0,1,1,-1,0,0],[0,-1,0,0,1,-1,0],[0,-R1,-R2,0,-R3,0,0],[0,0,R2,-R4,0,0,-1],[0,0,0,R4,R3,0,0],[1,0,0,0,0,0,0]])
b=np.array([0,0,0,0,0,-V1,-I1])

solucao=np.linalg.solve(A,b)

print('IA (mA) = ',solucao[0]*1000)
print('IB (mA) = ',solucao[1]*1000)
print('IC (mA) = ',solucao[2]*1000)
print('ID (mA) = ',solucao[3]*1000)
print('IE (mA) = ',solucao[4]*1000)
print('IF (mA) = ',solucao[5]*1000)
print('VI1 (V) = ',solucao[6])
