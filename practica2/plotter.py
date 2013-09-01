import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc



[a,b,c] = raw_input().split()
a = float(a)
b = float(b)
c = float(c)
lo = -10.0
hi = 10.0

[a2,b2,c2] = raw_input().split()
a2 = float(a2)
b2 = float(b2)
c2 = float(c2)

lo = float(input())
hi = float(input())

x2 = np.linspace(lo,hi,500)
y2 = a2*x2*x2 + b2*x2 + c2
x = np.linspace(lo,hi,500)
y = a*x*x + b*x + c

plt.plot(x,y,'k')
plt.plot(x2,y2,'k')
plt.xlabel('x')
plt.ylabel('y')
plt.title('hola')
plt.show()

