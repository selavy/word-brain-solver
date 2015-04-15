# word-brain-solver
word brain solver

Solves the iPhone game "Word Brain".  Currently only supports dictionaries on *nix based systems, and input
must be in a file of the form:

````
L S E
L I D
L O D
4 5
````

where the last line specifies the length of the words required.  Either put the input in input.board or pass
the name of the file with the --board argument.

Project requires:
+CMake
+Boost libs (program_options is not header only)

Build using cmake:
(in ./word-brain-solver)
mkdir build
cd build
cmake ..
make -j
cd src/solver
./word-brain-solver --help
