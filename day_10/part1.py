from typing import List, Set

INPUT_S="""\
7-F7-
.FJ|7
SJLL7
|F--J
LJ.LJ
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

# Parse Input
maze = []
for line in INPUT_S.splitlines():
    maze.append([ch for ch in line])

# Find Start Coordinates
for i, row in enumerate(maze):
    for j, _ in enumerate(row):
        if maze[i][j] == 'S':
            start = (i, j)

# Count length of the loop
steps = 0
coming_from = prev = (0, 0)
curr = start
while True:
    coming_from = prev
    prev = curr
    curr = move(curr, coming_from, maze)
    steps += 1

    if curr == start:
        break
    
print(f"Result: {int(steps/2)}")
