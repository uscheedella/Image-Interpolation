import matplotlib.pyplot as plt
from numpy import log as ln

times = []
cores = []

with open("scale.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        line = line.split(" ")
        if line[0] == "dt":
            times.append(float(line[2]))
    f.close()

n = len(times)
for i in range(n):
    cores.append(2**i)
    
plt.plot(cores,times)
plt.xlabel("Cores")
plt.ylabel("Compute Time (s)")
plt.show()
