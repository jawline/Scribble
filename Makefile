#Output executable
OUTPUT_DIR=./bin/
OUTPUT_FILE=scribble
EXECUTABLE=$(OUTPUT_DIR)$(OUTPUT_FILE)

#Directory information
SOURCE_DIR=src
GEN_DIR=gen
OBJ_DIR=obj

INSTALL_PATH = /usr/bin/scribble

#Generated files
GEN_FILES = $(GEN_DIR)/ScribbleLexer.cpp $(GEN_DIR)/ScribbleParser.cpp $(GEN_DIR)/SASMLexer.cpp $(GEN_DIR)/SASMParser.cpp

#Compiler settings
CC=g++
CFLAGS=-c -Wall -I $(SOURCE_DIR) -I $(GEN_DIR) -std=c++0x -g -O0 -pthread -lpthread
LDFLAGS=-pthread -lpthread

#Rules to find source code - NOTE: Look for a better way to scan directories. Nonrecursive works but is a bit ugly
SOURCES=$(GEN_FILES) $(wildcard $(SOURCE_DIR)/*.cpp) $(wildcard $(SOURCE_DIR)/**/*.cpp) $(wildcard $(SOURCE_DIR)/**/**/*.cpp)
OBJECTS=$(patsubst %.cpp,obj/%.o,$(SOURCES))

all: preprocess $(SOURCES) $(EXECUTABLE)

install: all
	@ln $(EXECUTABLE) $(INSTALL_PATH)

clean:
	@rm -r $(OBJ_DIR) $(EXECUTABLE) $(GEN_DIR)

#The executable rule compiles the set of objects into the target executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@


#These rule tells the compiler to generate an object from the source code.
$(OBJECTS) : $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

#The preprocess rules will generate the source files from the grammar and perform any operations that need to be performed before the compiler is run ( Such as version numbering )

preprocess: gen bison sasm_bison
	@sh scripts/build_number_increment.sh 
	@mkdir -p $(OUTPUT_DIR)

gen:
	@mkdir -p $(GEN_DIR)


#Preprocessor steps for the parser

bison: flex
	bison --verbose -d -o ./gen/ScribbleParser.cpp src/Scribble/Parser/Parser.yy

flex:
	flex -o ./gen/ScribbleLexer.cpp ./src/Scribble/Parser/Lexer.l

sasm_bison: sasm_flex
	bison --verbose -d -o ./gen/SASMParser.cpp src/SASM/Parser.yy

sasm_flex:
	flex -o ./gen/SASMLexer.cpp src/SASM/Lexer.l
