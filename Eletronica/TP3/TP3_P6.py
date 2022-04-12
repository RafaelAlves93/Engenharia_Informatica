from matplotlib import pyplot as plt
from math import pi
import numpy as np

f3=100
f5=50

P=1/f5
PA=P/1000
t=np.arange(0,2*P,PA)


v3=1*np.sin(2*pi*f3*t+pi)
v5=0.5*np.sin(2*pi*f5*t+0.5*pi)


vout=-3-v3+3*v5

plt.plot(t,v3,'g',t,v5,'k',t,vout,'r')
plt.axis([0,2*P,-6,2])
plt.grid()
plt.show()
