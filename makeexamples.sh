
#!/bin/sh
# Outputs std::map of input cfdg files

if [ $# -lt 1 ]
then
  echo "Usage: $0 file ..."
  echo "Takes the named files in the input directory and outputs a std::map that maps the name"
  echo "to the file contents."
  exit 1
fi

echo "const std::map<std::string, const char*>"
echo "CommandLineSystem::ExamplesMap{"

for f in $*
do
    printf "    { \"%s\", R\"&&&(" $f
    cat "input/$f"
    printf ")&&&\" },\n"
done

echo "};"
