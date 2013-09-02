import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
import sys


a = float(sys.argv[1])
b = float(sys.argv[2])
c = float(sys.argv[3])
a2 = float(sys.argv[4])
b2 = float(sys.argv[5])
c2 = float(sys.argv[6])
lo = float(sys.argv[7])
hi = float(sys.argv[8])


lo = -10.0
hi = 10.0


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

