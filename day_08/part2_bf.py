INPUT_S="""\
LR

11A = (11B, XXX)
11B = (XXX, 11Z)
11Z = (11B, XXX)
22A = (22B, XXX)
22B = (22C, 22C)
22C = (22Z, 22Z)
22Z = (22B, 22B)
XXX = (XXX, XXX)
"""


def allArrived(some_nodes, final_nodes):
    return all([True if node in final_nodes else False for node in some_nodes])

def computeSteps(map, instructions):
    
    n_steps = 0
    curr_nodes = [v for k, v in map.items() if k.endswith('A')]
    final_nodes = [v for k, v in map.items() if k.endswith('Z')]

    arrived = False
    while not arrived:
        for i in range(len(instructions)):
            for j in range(len(curr_nodes)):
                curr_nodes[j] = \
                    map[curr_nodes[j][0]] if instructions[i] == 'L' else map[curr_nodes[j][1]]

            n_steps += 1
            if allArrived(curr_nodes, final_nodes):
                arrived = True
                break
    
    return n_steps


# Parse Input
instructions, *nodes_elems =[line for line in INPUT_S.splitlines() if line]
nodes = [node_elem.replace(" ", "").split('=') for node_elem in nodes_elems]
network = { node[0] : tuple(node[1][1:-1].split(',')) for node in nodes}

print(f"Result: {computeSteps(network, instructions)}")
