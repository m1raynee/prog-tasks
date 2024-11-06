from itertools import product
from random import randint

for i in range(4):
        size = randint(10, 30)
        A = ['' for _ in range(size)]
        for x in range(size):
            for y in range(size):
                A[x] += str(randint(-99, 99))
                if y < size - 1:
                     A[x] += '\t'
            A[x] += '\n'

        with open(f"tasks/5/{i}.txt", "w+") as f:
             f.writelines(A)