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

def loadDictionary(filename, solutionSizes):
    def validWord(word):
        word = word.strip().lower()
        if len(word) not in solutionSizes:
            return False
        return word.isalpha()
    return [line.strip().lower() for line in open(filename) if validWord(line)]

GameState = namedtuple('GameState', ['board', 'currPos', 'finishedWords', 'visited', 'currentWord'])
HeapItem = namedtuple('HeapItem', ['priority', 'weight', 'heuristic', 'state'])
Pos = namedtuple('Pos', ['x', 'y'])

def createCheckCurrentWord(dictionary, solutionSizes):
    def checkCurrentWord(state):
        if (len(state.currentWord) in solutionSizes) and (state.currentWord in dictionary):
            return True
        return False
    return checkCurrentWord

def letterFrequencies(word):
    freq = {}
    for letter in word:
        if letter in freq:
            freq[letter] += 1
        else:
            freq[letter] = 1
    return freq
 
def getLetterFrequencies(board):
    freq = {}
    for row in board:
        for cell in row:
            if cell in freq:
                freq[cell] += 1
            else:
                freq[cell] = 1
    return freq

def filterWordOnFrequencies(word, letters):
    freq = letterFrequencies(word)
    for letter in freq:
        if letter not in letters:
            return False
        elif freq[letter] > letters[letter]:
            return False
        else:
            continue
    return True

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option('--filename', dest='filename', default='input.txt', help='input file')
    parser.add_option('--dict', dest='dictionary', default='/usr/share/dict/words', help='dictionary file to use for words')
    (options, args) = parser.parse_args()
    board, solutionSizes = readInput(options.filename)
    letterFreq = getLetterFrequencies(board)
    printBoard(board)
    print(letterFreq)
    print 'Solution sizes: ', solutionSizes
    print('Dictionary file: %s' % options.dictionary)
    dictionary = loadDictionary(options.dictionary, solutionSizes)
    print(len(dictionary))
    dictionary = [x for x in dictionary if filterWordOnFrequencies(x, letterFreq)]
    print(len(dictionary))
    print(dictionary)

