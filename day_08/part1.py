INPUT_S="""\
LLR

AAA = (BBB, BBB)
BBB = (AAA, ZZZ)
ZZZ = (ZZZ, ZZZ)
"""


def computeSteps(map, instructions):
    
    n_steps = 0
    curr_node = map["AAA"]
    final_node = map["ZZZ"]

    arrived = False
    while not arrived:
        for i in range(len(instructions)):
            print(f"{curr_node=}")
            if instructions[i] == 'L':
                curr_node = map[curr_node[0]]
            else:
                curr_node = map[curr_node[1]]
            
            n_steps += 1
            if curr_node == final_node:
                arrived = True
                break
        
    return n_steps


# Parse Input
instructions, *nodes_elems = [line for line in INPUT_S.splitlines() if line]
nodes = [node_elem.replace(" ", "").split('=') for node_elem in nodes_elems]
network = { node[0] : tuple(node[1][1:-1].split(',')) for node in nodes}

print(f"Result: {computeSteps(network, instructions)}")
