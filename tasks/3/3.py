def double_factorial(n):
    if n == 0 or n == 1:
        return 1
    return double_factorial(n-2) * n


for i in range(1, 5):
    print("%e" % (
        ((-52)**i) / double_factorial(3*(i)**2)
    ))
