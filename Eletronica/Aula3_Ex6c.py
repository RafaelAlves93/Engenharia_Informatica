import numpy as np

R1=1000
R2=2000
R3=2000
V1=1

A=np.array([[1,-1,-1],[R1,R2,0],[0,-R2,R3]])
b=np.array([0,V1,0])
solucao=np.linalg.solve(A,b)
print('I1 (mA)=',solucao[0]*1000)
print('I2 (mA)=',solucao[1]*1000)
print('I3 (mA)=',solucao[2]*1000)

IR1 = solucao[0]
VR1 = IR1*R1
print('IR1 (mA) =',IR1*1000)
print('VR1 (V)=',VR1)
