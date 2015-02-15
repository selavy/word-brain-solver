from optparse import OptionParser
import sys

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option('--filename', dest='filename', default='input.txt', help='input file')
    parser.add_option('--dict', dest='dictionary', default='/usr/share/dict/words', help='dictionary file to use for words')
    (options, args) = parser.parse_args()
    print('Opening: %s' % options.filename)
    board = []
    with open(options.filename) as f:
        s = [c.lower() for c in f.readline().split()]
        board.append(s)
        dim = len(s)
        for i in range(1, dim):
            s = [c.lower() for c in f.readline().split()]
            if len(s) != dim:
                raise ValueError('Input file format not correct!')
            board.append(s)
        s = f.readline().split()
        solutionSizes = [int(x) for x in s]
    print('Board: ')
    for row in board:
        print row
    print 'Solution sizes: ', solutionSizes
    print('Dictionary file: %s' % options.dictionary)
    maxWordSize = dim*dim
    def validWord(word):
        if len(word) > maxWordSize:
            return False
        return word.strip().lower().isalpha()
    dictionary = [line.strip().lower() for line in open(options.dictionary) if validWord(line)]
    for word in dictionary:
        print word


