import collections
from functools import reduce


INPUT_S="""\
Time:      7  15   30
Distance:  9  40  200
"""

# Parse Input
times, records = INPUT_S.splitlines()
times = list(map(int, times.split()[1:]))
records = list(map(int, records.split()[1:]))

print(f"{times=}")
print(f"{records=}")

j = 0
cnter = collections.Counter()
for time, record in zip(times, records):
    for i in range(1, time):
        v = i
        distance = v * (time - i)
        if distance > record:
            cnter[j] += 1
    j += 1

print(reduce(lambda x,y: x*y, cnter.values()))
