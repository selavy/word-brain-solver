from optparse import OptionParser
import sys

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option('--filename', dest='filename', default='input.txt', help='input file')
    (options, args) = parser.parse_args()
    filename = options.filename
    print('Opening: %s' % filename)
