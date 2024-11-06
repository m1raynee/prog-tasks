import random

for i in range(5):
    a = list({random.randint(-99, 99) for i in range(60+random.randint(-50, 0))})
    a.sort()
    with open(f"tasks/4/pointers/{i}.txt", "w+") as f:
        # f.write(f"{len(a)}\n")
        for x in a:
            f.write(f"{x}\n")
