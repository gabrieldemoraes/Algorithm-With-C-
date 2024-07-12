#Source code do curso Algoritmos com C++ por Fabio Galuppo
#Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
#Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
#This file is licensed to you under the MIT license

import matplotlib.pyplot as plt
import numpy as np

def f(N):
    return N * (0.05 * N + 0.9 * np.log2(N) + 0.05)

x = np.array(list(map(lambda i: 2 ** i, range(1, 6))))
y = np.array(list(map(f, x)))

plt.plot(y, color = 'r')

plt.plot(np.array(list(map(lambda i: i * i, x))), color = '#00FF00') # N^2
plt.plot(np.array(list(map(lambda i: i * np.log2(i), x))), color = '#0000FF') # N lg N
plt.plot(np.array(list(map(lambda i: i, x))), color = '#00FFFF') # N

plt.plot(np.array(list(map(lambda i: 1.25 * i * np.log2(i), x))), color = '#FF00FF') # Upper bound

plt.show()