import re


INPUT_S ="""\
Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
"""

max_red = 12
max_green = 13
max_blue = 14

def removeChars(chars_to_remove, from_string):
    for char in chars_to_remove:
        from_string = from_string.replace(char, '')
    
    return from_string

def findMax(from_game: str, color: str):
    tmp = []
    from_game = from_game.split()

    for i in range(len(from_game)):
        if (i+1) >= len(from_game):
            break
        if from_game[i+1] == color:
            tmp.append(int(from_game[i]))
    
    return max(tmp)

def isGamePossible(game: dict):
    if game["red"] > max_red:
        return False
    if game["green"] > max_green:
        return False
    if game["blue"] > max_blue:
        return False
    
    return True

# Parse input
games_s = INPUT_S.splitlines()
games_s = [game_s[game_s.find(':')+1:].strip() for game_s in games_s]
games_s = [removeChars([';', ','], game_s) for game_s in games_s]

MostCubesDict = {}
for idx, game_s in enumerate(games_s):
        MostCubesDict[idx] = {"red": findMax(game_s, "red")}
        MostCubesDict[idx]["blue"] = findMax(game_s, "blue")
        MostCubesDict[idx]["green"] = findMax(game_s, "green")

for entry in MostCubesDict:
    print(MostCubesDict[entry])

sum = 0
for game_id in MostCubesDict:
    if (isGamePossible(MostCubesDict[game_id])):
        sum += game_id + 1
        print(game_id+1)

print(sum)
