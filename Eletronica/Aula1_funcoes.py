import numpy as np
from matplotlib import pyplot as grafico
from math import pi
# funcao seno
# funcao seno = Amplitude * sin(2*pi*frequencia*t)
# vector tempo 0:0.01:1
tini=0
tfim=1
PA=0.001
t=np.arange(tini,tfim+PA,PA)
#print(t)
Amp=5
f=2
funcaoseno=Amp*np.sin(2*pi*f*t)
#print(funcaoseno)
funcaocoseno=Amp*np.cos(2*pi*f*t)
grafico.plot(t,funcaoseno,t,funcaocoseno)
grafico.grid()
grafico.show()
