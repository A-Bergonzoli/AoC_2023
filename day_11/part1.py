import collections
import itertools
from typing import Tuple


INPUT_S="""\
...#......
.......#..
#.........
..........
......#...
.#........
.........#
..........
.......#..
#...#.....
"""

def computePathLen(g1: Tuple[int, int], g2: Tuple[int, int]):
    dx = abs(g2[0] - g1[0])
    dy = abs(g2[1] - g1[1])

    if (g1[0] == g2[0]):  # same row
        return dy
    if (g1[1] == g2[1]):  # same col
        return dx

    return (dy) + (dx)


# Parse Input
lines =  INPUT_S.splitlines()
empty_rows = []
empty_cols = []
for i, row in enumerate(lines):
    if '#' not in row:
        empty_rows.append(i)
for j, col in enumerate(zip(*lines)):
    if '#' not in col:
        empty_cols.append(j)

# Expand the universe
for id in reversed(empty_rows):
    lines.insert(id+1, '+' * len(lines[0]))
for id in reversed(empty_cols):
    for i in range(len(lines)):
        lines[i] = lines[i][:id+1] + '*' + lines[i][id+1:]
for line in lines:
    print(line)

c = collections.Counter()
for i, row in enumerate(lines):
    for j, col in enumerate(row):
        if col == '#':
            c[i, j] += 1

sum = 0
for i, galaxy in enumerate(c.keys()):
    for galayx in list(c.keys())[i+1:]:
        sum += computePathLen(galaxy, galayx)
print(sum)
