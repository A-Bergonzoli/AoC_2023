INPUT_S="""\
0 3 6 9 12 15
1 3 6 10 15 21
10 13 16 21 30 45
"""


def allZeroes(history):
    zeroes = [True if elem == 0 else False for elem in history]
    return all(zeroes)

def computePrev(h):
    # base case
    if allZeroes(h):
        return 0
    
    diff = [h[i] - h[i-1] for i in range(1, len(h))]
    return h[0] - computePrev(diff)

# Parse Input
histories = []
for line in INPUT_S.splitlines():
    histories.append(list(map(int, line.split())))

sum = 0
for h in histories:
    sum += computePrev(h)

print(f"Result: {sum}")
