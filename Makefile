TARGET := Grid-Visualizer.exe

dumpmachine =$(shell g++ -dumpmachine | grep 64)
IS := $(shell [ -z $(dumpmachine)  ] && { echo "mingw32"; } || { echo "x86_64-w64-mingw32"; } )

Command_File := src/Commands.txt

SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin/$(IS)
LIB_DIR := lib/$(IS)
DEP_DIR := dep

EXE := $(BIN_DIR)/$(TARGET)
SRC := 	$(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.c)
OBJ :=  $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp)) \
		$(patsubst $(SRC_DIR)/%.c,  $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c  ))



CXXFLAGS = -I$(INC_DIR) -L$(LIB_DIR) -lmingw32 -lSDL2main -lSDL2 
DEP_FLAG =  -MMD -MF $(DEP_DIR)/$*.d

.phony: all build clean

all: build

build: $(DEP_DIR) $(OBJ_DIR) $(BIN_DIR) $(OBJ) $(EXE) $(DEP) $(Command_File)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -c -o $@ $< $(CXXFLAGS) $(DEP_FLAG)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc -c -o $@ $< $(CXXFLAGS) $(DEP_FLAG)

$(EXE): $(OBJ)
	g++ -o $@ $^ $(CXXFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)
$(DEP_DIR):
	mkdir -p $(DEP_DIR)

$(Command_File):
	touch $(Command_File)

run: build $(EXE)
	$(EXE)

clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*.exe $(DEP_DIR)/*