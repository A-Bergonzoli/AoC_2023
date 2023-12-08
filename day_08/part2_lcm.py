import math


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


def anyFinalNodeReached(node, final_nodes):
    return True if node in final_nodes else False

n_steps = 0
def computeSteps(map, instructions, start, ends):
    
    n_steps = 0

    arrived = False
    while not arrived:
        for i in range(len(instructions)):
            if instructions[i] == 'L':
                start = map[start[0]]
            else:
                start = map[start[1]]
            
            n_steps += 1
            if anyFinalNodeReached(start, ends):
                arrived = True
                break
        
    return n_steps
            

# Parse Input
instructions, *nodes_elems =[line for line in INPUT_S.splitlines() if line]
nodes = [node_elem.replace(" ", "").split('=') for node_elem in nodes_elems]
network = { node[0] : tuple(node[1][1:-1].split(',')) for node in nodes}
    
start_nodes = [v for k, v in network.items() if k.endswith('A')]
final_nodes = [v for k, v in network.items() if k.endswith('Z')]

n_steps = [computeSteps(network, instructions, curr_start, final_nodes) for (curr_start, _) in zip(start_nodes, final_nodes)]

print(f"Result: {math.lcm(*n_steps)}")
