import numpy as np

# multiplicar matrizes -> np.matmul(A,B)
#  N.M x M.W
# inversa de uma matriz -> np.linalg.inv(A)
A1=np.array([[3,4],[2,1]])
b=np.array([4,6])
A1_inv=np.linalg.inv(A1)
solucao1=np.matmul(A1_inv,b)
print(solucao1)

# calculo direto da solucao
solucao2=np.linalg.solve(A1,b)
print(solucao2)
