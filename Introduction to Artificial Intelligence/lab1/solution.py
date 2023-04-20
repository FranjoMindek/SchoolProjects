import argparse
from collections import deque
import heapq
import copy

class Node:
    state = ''      #naziv stanja
    value = 0       #ukupni trosak puta
    parent = None   #roditelj
    def __init__(self, state, value):
        self.state = state
        self.value = value
    def __repr__(self):
        return f'({self.state}, {self.value})'
    def __lt__(self, other):
        return self.value < other.value
    def __hash__(self):
        return hash(self.state)
    def __eq__(self, other):
        if isinstance(other, Node):
            return self.state == other.state
        return False
    def __ne__(self, other):
        return not __eq__(self, other)

class HNode:
    state = ''      #naziv stanja
    value = 0       #ukupni trosak puta
    heur = 0        #heuristika
    parent = None   #roditelj
    def __init__(self, state, value, heur):
        self.state = state
        self.value = value
        self.heur = heur
    def __repr__(self):
        return f'({self.state}, {self.value + self.heur})'
    def __lt__(self, other):
        return self.value + self.heur < other.value + other.heur
    def __hash__(self):
        return hash(self.state)
    def __eq__(self, other):
        if isinstance(other, HNode):
            return self.state == other.state
        return False
    def __ne__(self, other):
        return not __eq__(self, other)

#parsiaranje argumenata
parser = argparse.ArgumentParser(description='Configuration')
parser.add_argument('--alg')
parser.add_argument('--ss')
parser.add_argument('--h')
parser.add_argument('--check-optimistic', action='store_true')
parser.add_argument('--check-consistent', action='store_true')
args = parser.parse_args()

#citanje stanja
s0 = ''
goal = []
succDict = {}
heurDict = {}
distDict = {}

if args.h:
    heuristicFile = open(args.h, 'r')
    for line in heuristicFile:
        if line[0] == '#':  #ignoriraj komentare
            continue
        values = line.split(': ')
        heurDict[values[0]] = float(values[1].strip())
    heuristicFile.close()

if args.ss:
    count = 0
    statesFile = open(args.ss, 'r')
    for line in statesFile:
        if line[0] == '#':  #ignoriraj komentare
            continue
        if count == 0:
            s0 = line.strip()
            count = count + 1
        elif count == 1:
            goal = line.strip().split(' ')
            count = count + 1
        else:
            states = line.split(': ')
            if(len(states) > 1):
                stateValues = states[1].split(' ')
                stateValuePair = []
                for pair in stateValues:
                    values = pair.split(',')
                    info = Node(values[0], float(values[1].strip()))
                    stateValuePair.append(info)
                succDict[states[0]] = stateValuePair #imamo dictionary gdje: key = state, value = list(dict)
    statesFile.close()

#BFS
def expandStart(open, successors):
    for item in successors:
        itemCopy = copy.deepcopy(item)
        open.append(itemCopy)

def expandNotVisited(open, closed, current, successors):
    for item in successors:
        if item.state in closed:
            continue
        itemCopy = copy.deepcopy(item)
        itemCopy.parent = current
        itemCopy.value += current.value
        open.append(itemCopy)

#UCS
def expandStartUCS(open, successors):
    for item in successors:
        itemCopy = copy.deepcopy(item)
        heapq.heappush(open, itemCopy)

def expandNotVisitedUCS(open, closed, current, successors):
    for item in successors:
        if item.state in closed:
            continue
        itemCopy = copy.deepcopy(item)
        itemCopy.parent = current
        itemCopy.value += current.value
        heapq.heappush(open, itemCopy)

#ASTAR
def expandStartASTAR(open, inOpen, successors, heuristic):
    for item in successors:
        inOpen[item.state] = item.value
        itemCopy = HNode(item.state, item.value, heuristic[item.state])
        heapq.heappush(open, itemCopy)

def expandOptimalASTAR(open, inOpen, closed, current, successors, heur):
    for node in successors:
        nodeCopy = HNode(node.state, node.value + current.value, heur[node.state])
        nodeCopy.parent = current
        if nodeCopy.state in closed:
            if nodeCopy.value < closed[nodeCopy.state]:
                closed.pop(nodeCopy.state)
                heapq.heappush(open, nodeCopy)
                inOpen[nodeCopy.state] = nodeCopy.value
        elif nodeCopy.state not in inOpen:
            heapq.heappush(open, nodeCopy)
            inOpen[nodeCopy.state] = nodeCopy.value
        elif nodeCopy.value < inOpen[nodeCopy.state]:
            index = -1
            for i, old in enumerate(open):
                if nodeCopy == old:
                    index = i
                    break
            if index >= 0:
                del open[index]
                heapq.heappush(open, nodeCopy)


def BFS(s0, succ, goal): #returns (info value), (reference to solution node), (states visited)
    if s0 in goal:
        return True, None, 1
    statesVisited = 1
    closed = set()
    closed.add(s0)
    open = deque()
    expandStart(open, succ[s0])
    while open:
        n = open.popleft()
        statesVisited = statesVisited + 1
        closed.add(n.state)
        if n.state in goal:
            return True, n, statesVisited
        if n.state in succ:
            expandNotVisited(open, closed, n, succ[n.state])
    return False, None, statesVisited

def UCS(s0, succ, goal): #returns (info value), (reference to solution node), (states visited)
    if s0 in goal:
        return True, None, 1
    statesVisited = 1
    closed = set()
    closed.add(s0)
    open = []
    expandStartUCS(open, succ[s0])
    while open:
        n = heapq.heappop(open)
        statesVisited = statesVisited + 1
        closed.add(n.state)
        if n.state in goal:
            return True, n, statesVisited
        if n.state in succ:
            expandNotVisitedUCS(open, closed, n, succ[n.state])
    return False, None, statesVisited

def ASTAR(s0, succ, heur, goal): #returns (info value), (reference to solution node), (states visited)
    if s0 in goal:
        return True, None, 1
    statesVisited = 1
    closed = {}
    inOpen = {}
    startingNode = HNode(s0, 0, heur[s0])
    closed[s0] = startingNode.value
    open = []
    expandStartASTAR(open, inOpen, succ[s0], heur)
    while open:
        n = heapq.heappop(open)
        statesVisited = statesVisited + 1
        if n.state in goal:
            return True, n, statesVisited
        closed[n.state] = n.value
        if n.state in succ:
            expandOptimalASTAR(open, inOpen, closed, n, succ[n.state], heur)
        inOpen.pop(n.state)
    return False, None, statesVisited

def generatePathAndDepth(startingState, node, first):
    if node.parent:
        path, depth = generatePathAndDepth(startingState, node.parent, False)
        if first:
            return path + f'{node.state}', depth+1
        else:
            return path + f'{node.state} => ' , depth+1
    else:
        return f'{startingState} => {node.state} => ', 2

def printOutput(numberOfStates, cost, path, depth):
    print('[FOUND_SOLUTION]: yes')
    print('[STATES_VISITED]:', numberOfStates)
    print('[PATH_LENGTH]:', depth)
    print('[TOTAL_COST]:', cost)
    print('[PATH]:', path)
    print()

def algorithPrinter(res):
    if res[0] == True and res[2] != 1:    #slucaj cilj pronadjen
        path, depth = generatePathAndDepth(s0, res[1], True)
        printOutput(res[2], res[1].value, path, depth)
    elif res[0] == True:                        #slucaj je prvi cvor
        printOutput(1, 0, s0, 0)
    elif res[0] == False:                       #slucaj cilj nije pronadjen
        print('[FOUND SOLUTION]: no')
    else:                                       #slucaj koji se ne bi trebao dogoditi
        print('Algorithm return value error')

def distanceFromSolution(succ, goals):
    for goal in goals:
        distDict[goal] = 0.0
    for state in succ.keys():
        node = UCS(state, succ, goals)
        if node[1]:
            distDict[state] = node[1].value

def optimisticPrinter(dist, heur, path):
    print(f'# HEURISTIC-OPTIMISTIC {path}')
    optimistic = True
    for state,v in dist.items():
        hv = heur[state]
        if v >= hv:
            print(f'[CONDITION]: [OK] h({state}) <= h*: {hv} <= {v}')
        else:
            print(f'[CONDITION]: [ERR] h({state}) <= h*: {hv} <= {v}')
            optimistic = False
    if(optimistic):
        print('[CONCLUSION]: Heuristic is optimistic.')
    else:
        print('[CONCLUSION]: Heuristic is not optimistic.')
    print()

def consistentPrinter(succ, heur, path):
    print(f'# HEURISTIC-CONSISTENT {path}')
    consistent = True
    for state, successors in succ.items():
        sh = heur[state]
        for successor in successors:
            eh = heur[successor.state]
            if sh <= eh+successor.value:
                print(f'[CONDITION]: [OK] h({state}) <= h({successor.state}) + c: {sh} <= {eh} + {successor.value}')
            else:
                print(f'[CONDITION]: [ERR] h({state}) <= h({successor.state}) + c: {sh} <= {eh} + {successor.value}')
                consistent = False
    if (consistent):
        print('[CONCLUSION]: Heuristic is consistent.')
    else:
        print('[CONCLUSION]: Heuristic is not consistent.')
    print()

#pokretanje svega
if args.ss and args.alg:
    if args.alg == 'bfs':
        res = BFS(s0, succDict, goal)
        print('# BFS')
        algorithPrinter(res)
    elif args.alg == 'ucs':
        res = UCS(s0, succDict, goal)
        print('# UCS')
        algorithPrinter(res)
    elif args.alg == 'astar' and args.h:
        res = ASTAR(s0, succDict, heurDict, goal)
        print(f'# A-STAR {args.h}')
        algorithPrinter(res)

if args.h:
    if args.check_optimistic:
        distanceFromSolution(succDict, goal)
        optimisticPrinter(distDict, heurDict, args.h)
    if args.check_consistent:
        consistentPrinter(succDict, heurDict, args.h)
