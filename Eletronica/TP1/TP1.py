import numpy as np

V1=4
V2=-2
V3=-10
R1=1970
R2=1801
I2=-2.387/1000
I3=1.935/1000

#1: V1 + R1*I1 + R2(I1-I2) = 0
#2: V2 - V3 + R2(I2-I1) + R3(I2-I3) = 0
#3: R3(I3-I2) + I3*R4 + V3 = 0


#   R3          R4          I1

#   0           0           R1+R2           =   -V1+R2I2
#   (I2-I3)     0           R2              =   V3-V2-R2I2
#   I3-I2       I3          0               =   -V3

A=np.array([[0,0,R1+R2],[I2-I3,0,-R2],[I3-I2,I3,0]])

b=np.array([-V1+R2*I2,V3-V2-R2*I2,-V3])

solucao=np.linalg.solve(A,b)

R3=solucao[0]
R4=solucao[1]
I1=solucao[2]


print("R3 (Ohm):",np.round(R3,3))
print("R4 (Ohm):",np.round(R4,3))
print("I1 (mA):",np.round(I1*1000,3))

