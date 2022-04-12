import numpy as np
from matplotlib import pyplot as plt
from math import pi


f=50
Amplitude=10
P=f**-1
NPP=10000
PA=P/NPP
t=np.arange(0,5*P+PA,PA)
vin=Amplitude*np.sin(2*pi*f*t)
vout=vin.copy()


Vd=0.7 
Rd=100 
V2=5
Req = 500
R3 = 1000


for i in range(len(t)):
    if (vin[i]<V2-Vd):                  #Quando o diodo conduz
        vout[i]=-Vd-(R3+Rd)*((-vin[i]+V2-Vd)/(Rd+R3+Req))
    else:                               #Quando o diodo nao conduz
        vout[i]=vin[i]-V2
 

plt.plot(t,vin,t,vout)
plt.grid()
plt.show()
