name = pygdb
path = sample/sample.py
CC := gcc
CC_ARGS := -I./include/
SRC_DIR = src
BUILD_DIR = build

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CC_ARGS) $< -o $(BUILD_DIR)/$(name).o
	@chmod +x $(BUILD_DIR)/$(name).o

run: $(BUILD_DIR)/$(name).o 
	@$(BUILD_DIR)/$(name).o $(path)
