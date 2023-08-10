SHELL = powershell.exe

CXXFLAGS = -g 

INC_DIRS = \
	"../SFML/include" \
	"./include" \
	"."
LIB_DIRS = "../SFML/lib"

LDLIBS = -lsfml-graphics -lsfml-network -lsfml-audio -lsfml-window -lsfml-main -lsfml-system

BIN = DataVisualize

BUILD_DIR = ./bin
JUNK_DIR = $(BUILD_DIR)/junk
SRC_DIR = ./src

CPP_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(CPP_FILES:$(SRC_DIR)/%.cpp=$(JUNK_DIR)/%.o)
DEP_FILES = $(OBJ_FILES:%.o=%.d)

all: pre-build $(BUILD_DIR)/$(BIN)

pre-build:
	-mkdir "$(JUNK_DIR)"

$(BUILD_DIR)/$(BIN): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(^:%="%") -o "$@" $(LIB_DIRS:%=-L%) $(LDLIBS)

$(JUNK_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -c "$<" -o "$@" $(INC_DIRS:%=-I%)

-include $(DEP_FILES)

clean:
	-rm -force "$(BUILD_DIR)/*.exe"
	-rm -force "$(JUNK_DIR)/*.o"
	-rm -force "$(JUNK_DIR)/*.d"

rebuild: clean all