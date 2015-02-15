from optparse import OptionParser
import sys

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
    return board, dim, solutionSizes

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

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option('--filename', dest='filename', default='input.txt', help='input file')
    parser.add_option('--dict', dest='dictionary', default='/usr/share/dict/words', help='dictionary file to use for words')
    (options, args) = parser.parse_args()
    board, dim, solutionSizes = readInput(options.filename)
    printBoard(board)
    print 'Solution sizes: ', solutionSizes
    print('Dictionary file: %s' % options.dictionary)
    dictionary = loadDictionary(options.dictionary, dim)

