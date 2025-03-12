CC=g++
CFLAGS=-Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g3 -O0 -c
LDFLAGS=-Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g3 -O0
BUILD_DIR=./build/Debug
MODS_DIR=./modules

MODS_NAMES=chunkL.cpp strL.cpp

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

run: clean $(TARGET)
	cmd /d /c $(subst /,\,$(TARGET))

.PHONY: all clean run