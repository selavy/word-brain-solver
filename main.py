from optparse import OptionParser
import sys
from collections import namedtuple
import heapq

def readInput(filename):
    print('Opening: %s' % filename)
    board = []
    with open(filename) as f:
        def parseLine():
            return [c.lower() for c in f.readline().split()]
        s = parseLine()
        board.append(s)
        dim = len(s)
        for i in range(1, dim):
            s = parseLine()
            if len(s) != dim:
                raise ValueError('Input file format not correct.')
            board.append(s)
        s = f.readline().split()
        solutionSizes = [int(x) for x in s]
    return board, solutionSizes

def printBoard(board):
    print('Board: ')
    for row in board:
        print row

def loadDictionary(filename, dim):
    maxWordSize = dim*dim
    def validWord(word):
        if len(word) > maxWordSize:
            return False
        return word.strip().lower().isalpha()
    return [line.strip().lower() for line in open(filename) if validWord(line)]


GameState = namedtuple('GameState', ['board', 'currPos', 'finishedWords', 'visited', 'currentWord'])
HeapItem = namedtuple('HeapItem', ['priority', 'weight', 'heuristic', 'state'])
Pos = namedtuple('Pos', ['x', 'y'])

# Board
#-------------
#|0,0|0,1|0,2|
#|-----------|
#|1,0|1,1|1,2|
#|-----------|
#|2,0|2,1|2,2|
#-------------
def createInitialState(board):
    dim = len(board)
    return GameState(board=board, currPos=Pos(0, 0), finishedWords=[], visited=[[False for i in range(dim)] for i in range(dim)], currentWord='')

def createIsFinished(expectedWords):
    def isFinished(state):
        visited = state.visited
        for row in visited:
            for cell in row:
                if cell:
                    return False
        return len(state.finishedWords) == len(expectedWords)
    return isFinished

def createCheckCurrentWord(dictionary, solutionSizes):
    def checkCurrentWord(state):
        if (len(state.currentWord) in solutionSizes) and (state.currentWord in dictionary):
            return True
        return False
    return checkCurrentWord

def createGenerateMoves(checkCurrentWord):
    def generateMoves(state):
        if checkCurrentWord(state):
            state.finishedWords.append(state.currentWord)
            state.currentWord = ''
        return []
    return generateMoves


def AStarSearch(start, goal, moves, heuristic):
    Node = collections.namedtuple('Node', ['f', 'state', 'pred', 'move', 'g', 'h'])
    SAW = collections.namedtuple('SAW', ['state', 'action', 'weight'])
    Q = []
    def nodeToSAW(saw, prev):
        h = heuristic(saw.state)
        if not prev:
            g = saw.weight
        else:
            g = prev.g + saw.weight
        f = g + h
        return Node(f=f, state=saw.state, prev=prev, move=saw.action, g=g, h=h)
    for x in start:
        h = heuristic(x)
        heapq.heappush(Q, Node(f=h, state=x, pred=None, move=None, g=0, h=h))
    while heap:
        curr = heapq.heappop(heap)
        if goal(curr.state):
            print('Solution!')
            sys.exit(0)
        else:
            possibleMoves = moves(curr.state)
            for move in possibleMoves:
                saw = nodeToSAW(move, curr)
                heapq.heappush(heap, saw)
            if len(heap) == 0:
                print('No solution!')
                sys.exit(0)

def solver(board, dictionary, solutionSizes):
    def heuristic(state):
        return 0
    def goal(state):
        if len(state.words) == len(solutionSizes):
            return True
        return False
    USED = 'USED'
    BLANK = 'NONE'
    Pos = namedtuple('Pos', ['x', 'y'])
    State = namedtuple('State', ['board', 'words', 'curr', 'pos'])
    dim = len(boardce)
    start = []
    for x in range(dim):
        for y in range(dim):
            curr = board[x][y]
            b = board
            b[x][y] = USED
            start.append(State(board=b, words=[], curr=curr, pos=Pos(x,y)))
    print start

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option('--filename', dest='filename', default='input.txt', help='input file')
    parser.add_option('--dict', dest='dictionary', default='/usr/share/dict/words', help='dictionary file to use for words')
    (options, args) = parser.parse_args()
    board, solutionSizes = readInput(options.filename)
    printBoard(board)
    print 'Solution sizes: ', solutionSizes
    print('Dictionary file: %s' % options.dictionary)
# TODO (plesslie)
# filter dictionary on solution sizes
    dictionary = loadDictionary(options.dictionary, len(board))
    solver(board, dictionary, solutionSizes)

    # heap = [HeapItem(priority=1, weight=1, heuristic=0, state=createInitialState(board))]
    # isFinished = createIsFinished(solutionSizes)
    # checkCurrentWord = createCheckCurrentWord(dictionary, solutionSizes)
    # generateMoves = createGenerateMoves(checkCurrentWord)
    # while heap:
    #     state = heapq.heappop(heap).state
    #     print state
    #     if isFinished(state):
    #         print('Done words = %s' % str(state.finishedWords))
    #         sys.exit(0)
    #     moves = generateMoves(state)
    #     for move in moves:
    #         heapq.heappush(move)
    # print('Heap is empty. No solution found!')

