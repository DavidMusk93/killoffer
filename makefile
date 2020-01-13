BIN_DIR := bin
OBJ_DIR := obj

LOG_SRC := Logger.cc
LOG_OBJ := $(addprefix $(OBJ_DIR)/,$(LOG_SRC:%.cc=%.o))

SRC := $(wildcard *.cc)
OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:%.cc=%.o))

define build-object
@[ -d $(@D) ] || mkdir -p $(@D)
g++ -c $(CPPFLAGS) $1 $< -o $@
endef

define build-executable
@[ -d $(@D) ] || mkdir -p $(@D)
g++ $(CPPFLAGS) $^ -o $@
@echo "./$@" >$(MEMO)
endef

all: test

CPPFLAGS := -std=c++17 -Wall -g
MEMO := $(shell bash helper.sh 0)

$(OBJ): $(OBJ_DIR)/%.o: %.cc
	$(build-object)

X001 := 001-frog-jump
$(BIN_DIR)/$(X001): $(OBJ_DIR)/$(X001).o $(LOG_OBJ)
	$(build-executable)

X002 := 002-hold-water
$(BIN_DIR)/$(X002): $(OBJ_DIR)/$(X002).o $(LOG_OBJ)
	$(build-executable)

X003 := 003-balance-two-array
$(BIN_DIR)/$(X003): $(OBJ_DIR)/$(X003).o $(LOG_OBJ)
	$(build-executable)

.PHONY: clean

clean:
	@rm -rf $(BIN_DIR)
	@rm -rf $(OBJ_DIR)

.PHONY: run

run:
	@bash helper.sh 1

.PHONY: test

test:
	echo $(OBJ)
