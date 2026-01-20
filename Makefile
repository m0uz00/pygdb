name = pygdb
path = sample/sample.py
CC := gcc
CC_ARGS := -I./include/ $(shell python3-config --cflags)
LD_ARGS := -lpcre $(shell python3-config --ldflags)
SRC_DIR = src
BUILD_DIR = build
DBG_NAME = $(name)_debug

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 	
	mkdir -p $(BUILD_DIR)
	$(CC) $(CC_ARGS) -c $^ -o $@

$(BUILD_DIR)/$(DBG_NAME): $(SRC)	
	@echo $^
	mkdir -p $(BUILD_DIR)
	$(CC) $(CC_ARGS) $^ -o $@ -g $(LD_ARGS)
	chmod +x $@

debug: $(BUILD_DIR)/$(DBG_NAME)
	gdb --args $< $(path)

$(BUILD_DIR)/$(name): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LD_ARGS)
	chmod +x $@
	rm build/*.o

run: $(BUILD_DIR)/$(name)
	@echo " "
	@echo " "
	@$< $(path)

clean:
	rm -rf $(BUILD_DIR)/*
