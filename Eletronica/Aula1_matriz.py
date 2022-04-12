import numpy as np

#criar matriz manualmente
A=np.array([[1,2,3],[4,5,6],[7,8,9]])
#print(A)
#print(A.shape)

#criar matriz de uns
B=4*np.ones((3,4))
#print(B)

#criar matriz de zeros
C=np.zeros((3,4))
#print(C)

#criar matriz com uma constante
D=np.full((3,4),4.0)
#print(D)
#criar matriz identidade
E=np.identity(7)
#print(E)

#criar matriz valores aleatorios
F=10*np.random.rand(6,6)
#print(F)

# slicing
# obter a matriz 2x2 correspondente ao canto superior esquerdo
# linhas -> 0,1
# colunas -> 0,1
F1=F[0:2:1, 0:2:1]
#print(F1)

# obter a matriz 2x2 correspondente ao canto inferior direito
# linhas -> 4,5
# colunas -> 4,5
F2=F[4:6:1, 4:6:1]
#print(F2)
# linhas -> 1,3
# colunas -> 4,5
F3=F[1:4:2, 4:6:1]
#print(F3)

# para evitar alterar os valores da matriz original deve-se criar uma cópia
F3=F3.copy()
F3[0][0]=3
# desta forma F não é modificado

# operações com matrizes
G=10*np.random.rand(4,4)
print(G)
# todas as operações básicas de matemática +,-,x,/
G=G+10
print(G)
