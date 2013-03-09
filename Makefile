CC=g++
CFLAGS=-c -Wall -I src -I gen -std=c++0x
LDFLAGS=
EXECUTABLE=./bin/scribble
SOURCE_DIR=src
SOURCES=gen/Lexer.cpp gen/Parser.cpp $(wildcard $(SOURCE_DIR)/*.cpp) $(wildcard $(SOURCE_DIR)/**/*.cpp)
OBJECTS=$(patsubst %.cpp,obj/%.o,$(SOURCES))

all: preprocess $(SOURCES) $(EXECUTABLE)

test: all
	@$(EXECUTABLE) test.scribble

clean:
	rm -r ./obj/ $(EXECUTABLE) ./gen/

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

preprocess: gen bison

gen:
	@mkdir -p gen

bison: flex
	bison --verbose -d -o ./gen/Parser.cpp ./src/Parser/Parser.yy
flex:
	flex -o ./gen/Lexer.cpp ./src/Parser/Lexer.l

$(OBJECTS) : obj

obj:
	@mkdir -p $@

obj/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@
