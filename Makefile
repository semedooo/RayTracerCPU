CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
INCLUDES = -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN     = raytracer
VIEWER_BIN = ppm_viewer

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(BIN)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
SFML_CFLAGS := $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system)
SFML_LIBS   := $(shell pkg-config --libs sfml-graphics sfml-window sfml-system)
else
SFML_CFLAGS := -IC:/msys64/mingw64/include
SFML_LIBS   := -lsfml-graphics -lsfml-window -lsfml-system
endif

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SFML_CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: $(BIN)
	./$(BIN)

viewer: PPMViewerCLI.cpp $(SRC_DIR)/ShowPPM.cpp include/ShowPPM.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SFML_CFLAGS) -o $(VIEWER_BIN) PPMViewerCLI.cpp $(SRC_DIR)/ShowPPM.cpp $(SFML_LIBS)

clean:
	rm -rf $(OBJ_DIR) $(BIN) $(VIEWER_BIN)

.PHONY: all run viewer clean
