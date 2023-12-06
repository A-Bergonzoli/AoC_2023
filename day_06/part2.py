from functools import reduce


INPUT_S="""\
Time: 71530
Distance: 940200
"""

# Parse Input
times, records = INPUT_S.splitlines()
times = list(map(int, times.split()[1:]))
records = list(map(int, records.split()[1:]))

print(f"{times=}")
print(f"{records=}")

cnter = 0
for time, record in zip(times, records):
    for i in range(1, time):
        v = i
        distance = v * (time - i)
        if distance > record:
            cnter = time - 2*i + 1
            break

print(cnter)
