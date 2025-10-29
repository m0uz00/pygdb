name = pygdb
path = sample/sample.py
CC := gcc
CC_ARGS := -I./include/
SRC_DIR = src
BUILD_DIR = build

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CC_ARGS) -c $< -o $@

$(BUILD_DIR)/$(name): $(OBJ)
	$(CC) $(OBJ) -o $@
	chmod +x $@
	rm build/*.o

run: $(BUILD_DIR)/$(name)
	@$(BUILD_DIR)/$(name) $(path)

clean:
	rm -rf $(BUILD_DIR)/*
