import matplotlib.pyplot as plt
import numpy as np

x_bar = list(range(0, 11))
height = [ 0, 2, 1, 3, 1, 2, 0, 4, 2, 3, 1 ]

plt.bar(x_bar, height, width = 0.95, color = ['red', 'blue'])

plt.xticks(np.arange(0, 16, 1))
plt.yticks(np.arange(0, 8, 1))
plt.grid(which='major', axis='y')

plt.xlabel('index')
plt.ylabel('height')
plt.title('Hold Water')

plt.show()
