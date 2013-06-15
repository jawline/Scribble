CC=g++
CFLAGS=-c -Wall -I src -I gen -std=c++0x -g -O0 -pthread -lpthread
LDFLAGS=-pthread -lpthread
EXECUTABLE=./bin/scribble
SOURCE_DIR=src
SOURCES=gen/Lexer.cpp gen/Parser.cpp gen/SASMLexer.cpp gen/SASMParser.cpp $(wildcard $(SOURCE_DIR)/*.cpp) $(wildcard $(SOURCE_DIR)/**/*.cpp)
OBJECTS=$(patsubst %.cpp,obj/%.o,$(SOURCES))

all: preprocess $(SOURCES) $(EXECUTABLE)

clean:
	rm -r ./obj/ $(EXECUTABLE) ./gen/

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

preprocess: gen bison sasm_bison
	@sh build_number_increment.sh 

gen:
	@mkdir -p gen

bison: flex
	bison --verbose -d -o ./gen/Parser.cpp ./src/Parser/Parser.yy
flex:
	flex -o ./gen/Lexer.cpp ./src/Parser/Lexer.l

sasm_bison: sasm_flex
	bison --verbose -d -o ./gen/SASMParser.cpp ./src/SASM/Parser.yy

sasm_flex:
	flex -o ./gen/SASMLexer.cpp ./src/SASM/Lexer.l

$(OBJECTS) : obj

obj:
	@mkdir -p $@

obj/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@
