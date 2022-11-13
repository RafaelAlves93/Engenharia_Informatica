# comentario

import numpy as np

# Criaçao manuel de vectores
v1=np.array([1,2,3,4,5,6,7,8,9,10])
print(v1)
print(v1.dtype)

# Criaçao manuel de vectores de reais
v2=np.array([1.1,2,3,4,5,6,7,8,9,10])
print(v2)
print(v2.dtype)

v3=v1+v2
print(v3)
print(v3.dtype)

v4=v2**2 #v3+3.12
print(v4)


#CRIAÇÃO DE VECTORES DE FORMA AUTOMÁTICA
# vector - np.arange(inicio,fim+incremento,incremento)
ini=-100
fim=100
inc=1
vector=np.arange(ini,fim+inc,inc)
print(vector)

#slicing - apenas os elementos negativos
vector_neg1=vector[0:100:1]
vector_neg2=vector[0:-101:1] #indexação negativa
#print(vector_neg1)
#print(vector_neg2)

#slicing - apenas os elementos positivos
vector_pos=vector[101:] #[101:200:1]
print(vector_pos)

#slicing - apenas os elementos impares positivos
vector_pos_impares=vector[101::2] 
print(vector_pos_impares)

