CC=g++
CFLAGS=-std=c++20 -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g3 -O0 -c
LDFLAGS=-std=c++20 -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g3 -O0
BUILD_DIR=./build/Debug
MODS_DIR=./modules

MODS_NAMES=chunkL.cpp strL.cpp files.cpp

OBJS_NAMES = $(MODS_NAMES:.cpp=.o)
OBJS=$(addprefix $(BUILD_DIR)/,$(OBJS_NAMES))

TARGET_NAME = outDebug.exe
TARGET = $(BUILD_DIR)/$(TARGET_NAME)

all: $(TARGET)

$(TARGET): $(OBJS) $(BUILD_DIR)/main.o
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(BUILD_DIR)/main.o

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

$(BUILD_DIR)/%.o: $(MODS_DIR)/%.cpp
	echo $@ $<
	$(CC) $(CFLAGS) $< -o $@

recompile: clean $(TARGET)

run: $(TARGET)
	cmd /d /c $(subst /,\,$(TARGET))

rerun: recompile run

.PHONY: all clean run rerun recompile