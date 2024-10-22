import matplotlib.pyplot as plt
import numpy as np

file = open("times.csv", "r")

qs_arr = np.empty(10, dtype=float)
bs_arr = np.empty(10, dtype=float)
problem_sizes = np.empty(10, dtype=int)
read = False
i = 0
j = 0
for line in file:
	if read and j == 0:
		qs_arr[i] = float(line.split(",")[1])
		problem_sizes[i] = int(line.split(",")[0])
		i += 1
		if i == 10:
			i = 0
			j = 1
			read = False
	if read and j == 1:
		bs_arr[i] = float(line.split(",")[1])
		i += 1
	if line.find("size") != -1:
		read = True

plt.figure(0)
plt.plot(problem_sizes, qs_arr, label="quick sort")
plt.plot(problem_sizes, bs_arr, label="bubble sort")

plt.yscale("log", base=2)

plt.xlabel("Tamanho do problema")
plt.ylabel("Tempo de execução (s)")
plt.legend()
plt.show()