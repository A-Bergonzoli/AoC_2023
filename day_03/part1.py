import collections
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

def isPartNumber(num_s: str, x: int, last_y: int, heat_map: Set[Tuple[int, int]]):
    match = []
    ys = list(range(last_y - len(num_s), last_y))

    for y in ys:
        match.append(True) if (x, y) in heat_map else match.append(False)
    
    return any(match)

lines = INPUT_S.splitlines()

max_row = len(lines)
max_col = len(lines[0])

heat_map: Set[Tuple[int, int]] = set()

for i, line in enumerate(lines):
    for j, char in enumerate(line):
        if (char != '.' and not char.isdigit()):
            for row in range(i-1, i+2):
                for col in range(j-1, j+2):
                    if (0 <= row and row < max_row and 
                        0 <= col and col < max_col):  # this check is superfluous
                        heat_map.add((row, col))

sum = 0
digit_buf = ""
for i, line in enumerate(lines):
    for j, char in enumerate(line):
        if (char.isdigit()):
            digit_buf += char
        elif len(digit_buf) > 0:
            if (isPartNumber(digit_buf, i, j, heat_map)):
                sum += int(digit_buf)         
            digit_buf = ""

print(f"Result: {sum}")
