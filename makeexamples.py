import os
import sys

def print_cfdg(cfdg_name):
    cfdg_file = os.path.join('input', cfdg_name)
    if not os.path.exists(cfdg_file):
        sys.stderr.write('Cannot find file: %s\n' % cfdg_file)
        sys.exit(2)

    transtable = str.maketrans({'"': r'\"', "…": r'\u2026'})
    with open(cfdg_file, 'r') as fp:
        for line in fp:
            sys.stdout.write('u8"')
            sys.stdout.write(line.rstrip().translate(transtable))
            print('\\n"')


def print_examples(cfdg_files):
    print('const std::map<std::string, std::pair<const char*, const char*>>')
    print('AbstractSystem::ExamplesMap{')

    for cfdg in cfdg_files:
        if cfdg.endswith('_v2.cfdg'):
            pass
        else:
            print('    { "%s", {' % cfdg)
            print_cfdg(cfdg)
            print(' ,')
            print_cfdg(cfdg.replace('.cfdg', '_v2.cfdg'))
            print('    } },')


    print('};')


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: %s file ...' % sys.argv[0])
        print('Takes the named files in the input directory and writes to standard output a ')
        print('std::map that maps the name to the file contents.')
        sys.exit(1)

    print_examples(sys.argv[1:])
    sys.exit(0)
