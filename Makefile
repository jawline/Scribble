#Output executable
OUTPUT_DIR=./bin/
OUTPUT_FILE=scribble
OUTPUT_LIB=libscribble.so
EXECUTABLE=$(OUTPUT_DIR)$(OUTPUT_FILE)
LIBRARY=$(OUTPUT_DIR)$(OUTPUT_LIB)
 
#Directory information
SOURCE_DIR=src
GEN_DIR=gen
OBJ_DIR=obj
 
INSTALL_EXE_PATH = /usr/bin/
INSTALL_LIB_PATH = /usr/lib/
 
#Generated files
GEN_FILES = $(GEN_DIR)/ScribbleLexer.cpp $(GEN_DIR)/ScribbleParser.cpp $(GEN_DIR)/SASMLexer.cpp $(GEN_DIR)/SASMParser.cpp
 
#File which is touched to verify parser is generated
GENERATED_FILE= $(GEN_DIR)/generated_parser
 
#Compiler settings
CC=g++
STD_VER=c++0x
CFLAGS=-c -Wall -I $(SOURCE_DIR) -I $(GEN_DIR) -std=$(STD_VER) -g -fPIC
LDFLAGS=-pthread -lpthread -fPIC -g
 
#Rules to find source code - TODO: Look for a better way to scan directories. Nonrecursive works but is a bit ugly
SOURCES=$(GEN_FILES) $(wildcard $(SOURCE_DIR)/*.cpp) $(wildcard $(SOURCE_DIR)/**/*.cpp) $(wildcard $(SOURCE_DIR)/**/**/*.cpp)
OBJECTS=$(patsubst %.cpp,obj/%.o,$(SOURCES))
 
all: warn preprocess $(SOURCES) $(EXECUTABLE) $(LIBRARY)
 
warn:
ifeq ($(wildcard $(GENERATED_FILE)),)
	@echo "Before first compile 'make generate_parser' must be run"
	exit 1
endif
 
install:
	@cp $(LIBRARY) $(INSTALL_LIB_PATH)$(OUTPUT_LIB)
	@cp $(EXECUTABLE) $(INSTALL_EXE_PATH)$(OUTPUT_FILE)
 
remove:
	-rm $(INSTALL_LIB_PATH)$(OUTPUT_LIB)
	-rm $(INSTALL_EXE_PATH)$(OUTPUT_FILE)
 
clean:
	-rm -f -r $(OBJ_DIR) $(EXECUTABLE) $(LIBRARY)
 
#The executable rule compiles the set of objects into the target executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
 
$(LIBRARY): $(OBJECTS)
	$(CC) $(LDFLAGS)  -shared  $(OBJECTS) -o $@
 
#These rule tells the compiler to generate an object from the source code.
$(OBJECTS) : $(OBJ_DIR)
 
$(OBJ_DIR):
	-@mkdir -p $@
 
$(OBJ_DIR)/%.o: %.cpp
	-@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@
 
#The preprocess rules will update the build number
preprocess:
	-@mkdir -p $(OUTPUT_DIR)
	-@sh scripts/build_number_increment.sh
 
generate_parser: generate_parser_folder bison sasm_bison
generate_parser_folder:
	@mkdir -p $(GEN_DIR)
	@touch $(GENERATED_FILE)
 
#Preprocessor steps for the parser
 
bison: flex
	bison --verbose -d -o ./gen/ScribbleParser.cpp src/Scribble/Parser/Parser.yy
 
flex:
	flex -o ./gen/ScribbleLexer.cpp ./src/Scribble/Parser/Lexer.l
 
sasm_bison: sasm_flex
	bison --verbose -d -o ./gen/SASMParser.cpp src/SASM/Parser.yy
 
sasm_flex:
	flex -o ./gen/SASMLexer.cpp src/SASM/Lexer.l
 
clean_parser:
	-rm -f -r $(GEN_DIR)