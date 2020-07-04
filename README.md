# Scribble Language

Scribble is a high level programming language, register based IR, and interpreter for embedded scripting applications in large programs.

# Building

To compile Scribble bison, flex and a version of g++ must be installed.

The program should compile on windows however it is untested and Linux is recommended.
The program has been tested on windows through Cygwin and works. After the parser is generated
(make generate_parser) the source could be compatable with most C++ compilers on windows, but this is not guarenteed

To compile the program run the program make generate_parser and then make when inside the Scribble directory.
For example if the Scribble directory was `~/Scribble` then you would type 
`cd ~/Scribble && make generate_parser && make` this will place the generated executable in `~/Scribble/bin/`

To install Scribble to /usr/bin type make install with elevated privileges (E.g. sudo make install)

# Getting Started

Once built, we should have a build of scribble (The scribble executable contains the high level parser, IR parser, and the interpreter). Running `./bin/scribble` we expect output like:
```
Usage: ./bin/scribble [OPTIONS] file
Options:
-v --version: version information
-r --runtime: output the time it takes for a script to execute
```

A good place to start is to execute the Scribble self-tests. To run these tests on the command line execute `./bin/scribble examples/executeTests.sc`. To make your own scribble programs, create a new script 'FILENAME.sc' and

# Language Documentation

A full report documenting all the features of the language [is available here](https://github.com/jawline/Scribble/blob/master/docs/Final%20Report/Report.pdf).
