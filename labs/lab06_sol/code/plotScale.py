import numpy as np
import matplotlib.pyplot as plt
from numpy import log as ln

times_laptop = []
times_cascades = []
cores = []

with open("scale_laptop.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        line = line.split(" ")
        if line[0] == "dt":
            times_laptop.append(float(line[2]))
    f.close()

with open("scale_cascades.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        line = line.split(" ")
        if line[0] == "dt":
            times_cascades.append(float(line[2]))
    f.close()

n = len(times_laptop)
for i in range(n):
    cores.append(2**i)
    
plt.figure()
plt.loglog(cores, times_laptop, "-o", label="laptop", linewidth=2)
plt.loglog(cores, times_cascades, "-o", label="cascades", linewidth=2)
plt.legend()
plt.xlabel("Cores")
plt.ylabel("Compute Time (s)")


converge = []

with open("converge.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        line = line.split(" ")
        if line[0] == "estPi":
            converge.append(float(line[2]))
    f.close()

n = 10**np.arange(len(converge),dtype=np.int64) * 100
converge = np.array(converge)

relerr = np.abs(converge - np.pi)/np.pi

plt.figure()
plt.loglog(n, relerr, "-o", label="Relative Error", linewidth=2)
plt.title("Relative error wrt $\pi$")
plt.xlabel("N Samples")
plt.ylabel("Error")

plt.show()
