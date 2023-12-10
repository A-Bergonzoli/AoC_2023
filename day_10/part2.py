from collections import Counter
from typing import List, Set

INPUT_S="""\
FF7FSF7F7F7F7F7F---7
L|LJ||||||||||||F--J
FL-7LJLJ||||||LJL-77
F--JF--7||LJLJ7F7FJ-
L---JF-JLJ.||-FJLJJ7
|F|F-JF---7F7-L7L|7|
|FFJF7L7F-JF7|JL---7
7-L-JL7||F7|L7F-7F7|
L.L7LFJ|||||FJL7||LJ
L7JLJL-JLJLJL--JLJ.L
"""

def computePossibleMoves(current, maze):
    up = (current[0] - 1, current[1])
    down = (current[0] + 1, current[1])
    left = (current[0], current[1] - 1)
    right = (current[0], current[1] + 1)

    current_tile = maze[current[0]][current[1]]

    if current_tile == '|':
        return up, down
    elif current_tile == '-':
        return left, right
    elif current_tile == 'L':
        return up, right
    elif current_tile == 'J':
        return up, left
    elif current_tile == 'F':
        return down, right
    else: #current_tile == '7':
        return down, left
        
def move(curr, coming_from, maze):
    maybe1, maybe2 = computePossibleMoves(curr, maze)

    return maybe1 if maybe1 != coming_from else maybe2

def isInside(i, j, c, maze):
    cnt_left = 0
    # maze[25][108] = '|'  # for the actual input
    maze[0][4] = '7'  # for the toy input

    if c[i, j] > 0:
        # point on loop
        return False
    
    for col in range(j-1, 0-1, -1):
        if c[i, col] > 0 and maze[i][col] in '|LJ':
            cnt_left += 1

    return cnt_left % 2 != 0

# Parse Input
maze = []
for line in INPUT_S.splitlines():
    maze.append([ch for ch in line])

# Find start coordinates
for i, row in enumerate(maze):
    for j, _ in enumerate(row):
        if maze[i][j] == 'S':
            start = (i, j)

# Fill Counter with loop-tile locations
coming_from = prev = (0, 0)
curr = start
c = Counter()
while True:
    coming_from = prev
    prev = curr
    curr = move(curr, coming_from, maze)
    c[(curr[0], curr[1])] += 1
    
    if curr == start:
        break

# Count tiles enclosed by loop
num_inside = 0
for i, row in enumerate(maze):
    for j, tile in enumerate(row):
        if isInside(i, j, c, maze):
            num_inside += 1

print(f"Result: {num_inside}")
