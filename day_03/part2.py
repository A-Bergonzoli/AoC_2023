import collections
import itertools
from typing import Set, Tuple


INPUT_S = """\
467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..
"""

class Number():
    def __init__(self, number_s: str, row: int, col: int):
        self.number_s_ = number_s
        self.position_ = (row, col)
        self.sz_ = len(number_s)

    def IsPartNumberFor(self, gear: Set[Tuple[int, int]]):
        match = []
        cols = list(range(self.position_[1], self.position_[1] + self.sz_))

        for col in cols:
            match.append(True) if (self.position_[0], col) in gear else match.append(False)

        return any(match)

    @property
    def ValueAsInt(self):
        return int(self.number_s_)

lines = INPUT_S.splitlines()

numbers = []
buf = ""
for row, line in enumerate(lines):
    for col, ch in enumerate(line):
        if (ch.isdigit()):
            buf += ch
        elif len(buf) > 0:
            numbers.append(Number(buf, row, col-len(buf)))
            buf = ""

maybe_gears = []
for i, line in enumerate(lines):
    for j, char in enumerate(line):
        if (char == '*'):
            maybe_gears.append((i, j))

maybe_gears_heat_maps = []
for idx, maybe_gear in enumerate(maybe_gears):
    row = maybe_gear[0]
    col = maybe_gear[1]
    maybe_gears_heat_maps.append(set())
    for i in range(row - 1, row + 2):
        for j in range(col - 1, col + 2):
            maybe_gears_heat_maps[idx].add((i, j))

parts_per_maybe_gear = [0 for elem in maybe_gears_heat_maps]
for num in numbers:
    for idx, heat_map in enumerate(maybe_gears_heat_maps):
        if (num.IsPartNumberFor(heat_map)):
            parts_per_maybe_gear[idx] += 1

gears_heat_map = [heat_map for idx, heat_map in enumerate(maybe_gears_heat_maps) if parts_per_maybe_gear[idx] == 2]

sum = 0
for elem in gears_heat_map:
    for n1, n2 in itertools.combinations(numbers, 2):
        if (n1.IsPartNumberFor(elem)) and n2.IsPartNumberFor(elem):
            sum += n1.ValueAsInt * n2.ValueAsInt
            print(sum)

print(f"Result: {sum}")
