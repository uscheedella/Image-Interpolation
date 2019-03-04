import numpy as np
import matplotlib.pyplot as plt


row_times = np.array([0.0000003800, 0.0000013000, 0.0000052200, 0.0000255400, 0.0000896800, 0.0003911600, 0.0015848800, 0.0066128600, 0.0249078800, 0.1010645400])

col_times = np.array([0.0000003800, 0.0000014800, 0.0000054200, 0.0000249200, 0.0000892000, 0.0004509200, 0.0029247200, 0.0154923400, 0.1498281800, 0.8327762400])

Ns = np.array([10, 20, 40, 80, 160, 320, 640, 1280, 2560, 5120])


plt.figure()
plt.loglog(Ns, row_times, label="Row-Oriented Timings", linewidth=2)
plt.loglog(Ns, col_times, label="Col-Oriented Timings", linewidth=2)

plt.vlines([89, 270, 1279], 1e-6, 1e0, color='red')

plt.legend()
plt.title("Matvec Performance")
plt.xlabel("$N$")
plt.ylabel("time (s)")