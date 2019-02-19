# Scribble Language
To compile Scribble bison, flex and a version of g++ with C++11 support must be installed and in the path.

If using a version of these which has not been installed to your path by default you can add it to the path by typing export PATH=$PATH:Path/To/Tool/Directory on Linux and other UNIX systems.

The program should compile on windows however it is untested and Linux is recommended.
The program has been tested on windows through Cygwin and works. After the parser is generated
(make generate_parser) the source could be compatable with most C++ compilers on windows, but this is not guarenteed

To compile the program run the program make generate_parser and then make when inside the Scribble directory.
For example if the Scribble directory was ~/Scribble then you would type 
"cd ~/Scribble && make generate_parser && make" this will place the generated executable in ~/Scribble/bin/

To install Scribble to /usr/bin type make install with elevated privileges (E.g. sudo make install)

Usage: ./bin/scribble [OPTIONS] file
Options:
-v --version: version information
-r --runtime: output the time it takes for a script to execute

