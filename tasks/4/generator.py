import random

for i in range(10):
    a = list({random.randint(-100, 100) for i in range(60+random.randint(-50, 50))})
    a.sort()
    with open(f"tasks/4/files/{i}.txt", "w+") as f:
        f.write(f"{len(a)}\n")
        for x in a:
            f.write(f"{x}\n")
