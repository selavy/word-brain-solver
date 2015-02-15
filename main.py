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
    heap = [HeapItem(priority=1, weight=1, heuristic=0, state=createInitialState(board))]
    isFinished = createIsFinished(solutionSizes)
    checkCurrentWord = createCheckCurrentWord(dictionary, solutionSizes)
    generateMoves = createGenerateMoves(checkCurrentWord)
    while heap:
        state = heapq.heappop(heap).state
        print state
        if isFinished(state):
            print('Done words = %s' % str(state.finishedWords))
            sys.exit(0)
        moves = generateMoves(state)
        for move in moves:
            heapq.heappush(move)
    print('Heap is empty. No solution found!')

