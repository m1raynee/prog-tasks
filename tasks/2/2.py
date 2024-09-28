from itertools import product

import matplotlib.pyplot as plt
import numpy as np

# plot
fig, ax = plt.subplots()

x = []
y = []

a = 3
b = 10

def is_inside(x, y):
    ...

for dot in product(range(-5000, 5000), repeat=2):
    dot = np.array(dot) / 100

    if is_inside(*dot):
        x, y = dot

ax.scatter(x, y)