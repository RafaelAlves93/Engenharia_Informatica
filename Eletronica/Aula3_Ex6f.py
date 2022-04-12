import numpy as np

R1=1000
R2=2000
R3=2000
V1=1

A=np.array([[1,-1,-1],[R1,R2,0],[0,-R2,R3]])
b=np.array([0,V1,0])
solucao=np.linalg.solve(A,b)
I1=solucao[0]
I2=solucao[1]
I3=solucao[2]

Modulo_PV1=V1*I1
Modulo_PR1=R1*I1**2
Modulo_PR2=R2*I2**2
Modulo_PR3=R3*I3**2

if Modulo_PV1==(Modulo_PR1+Modulo_PR2+Modulo_PR3):
    print('Verifica-se o principio da conservaçao')
else:
    print('Ocorreu um erro de calculo')
