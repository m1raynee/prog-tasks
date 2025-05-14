from faker import Faker
import random

fake = Faker("ru-RU")

def generate_executors(*, total=50):
    for i in range(total):
        print(fake.ssn(), fake.name(), fake.address(), sep='$')

def generate_tasks(*, total=50):
    r = random.Random()
    for i in range(total):
        num_of_workers = r.randint(1, 10)
        is_finished = r.random() > 0.5
        r.seed(random.randint(1, 35))
        executors = ' '.join(map(str, sorted(r.sample(range(100), k=num_of_workers))))
        name = fake.bs()
        r.seed(name)

        print(
            name,
            rate:=r.randint(25, 200),
            r.randint(50, 1000),
            ((rate+r.randint(-rate//10, rate//10))*num_of_workers if is_finished else ''),
            (fake.date_this_decade(after_today=False).strftime("%Y %m %d") if is_finished else ''),
            executors,
            sep="|"
        )

generate_tasks(total=100)