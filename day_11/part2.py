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

c = collections.Counter()
for i, row in enumerate(lines):
    for j, col in enumerate(row):
        if col == '#':
            tmp_x = i + sum(99 for r in empty_rows if r < i)  # 999999 for actual input
            tmp_y = j + sum(99 for c in empty_cols if c < j)
            c[tmp_x, tmp_y] += 1

sum = 0
for i, galaxy in enumerate(c.keys()):
    for galayx in list(c.keys())[i+1:]:
        sum += computePathLen(galaxy, galayx)
print(sum)
