import os
import sys

def print_cfdg(cfdg_name):
    cfdg_file = os.path.join('input', cfdg_name)
    if not os.path.exists(cfdg_file):
        sys.stderr.write('Cannot find file: %s\n' % cfdg_file)
        sys.exit(2)

    sys.stdout.write('    { "%s", R"&&&(' % cfdg_name)
    length = 0

    with open(cfdg_file, 'r') as fp:
        for line in fp:
            sys.stdout.write(line)
            length += len(line)
            if line == '\n' and length > 16000:
                sys.stdout.write(')&&&" R"&&&(')
                length = 0
            if length > 16384:
                sys.stderr.write('String exceeds 16384 characters: %s\n' % cfdg_file)
                sys.exit(3)

    print(')&&&" },')

def print_examples(cfdg_files):
    print('const std::map<std::string, const char*>')
    print('CommandLineSystem::ExamplesMap{')

    for cfdg in cfdg_files:
        print_cfdg(cfdg)

    print('};')


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: %s file ...' % sys.argv[0])
        print('Takes the named files in the input directory and writes to standard output a ')
        print('std::map that maps the name to the file contents.')
        sys.exit(1)

    print_examples(sys.argv[1:])
    sys.exit(0)
