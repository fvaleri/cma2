CC = gcc
CFLAGS = -O2 -Wall -W -std=c99
LDFLAGS =
LDLIBS =
SRC = src
BUILD = build
BINARY = $(BUILD)/justify

# expands to source file paths in src directory
SRCS = $(wildcard $(SRC)/*.c)
# expands to object file paths in build directory
# example: src/main.c src/utils.c -> build/obj/main.o build/obj/utils.o
OBJS = $(addprefix $(BUILD)/obj/,$(notdir $(SRCS:.c=.o)))

all: $(BINARY)

# multi-file build
# stage1: compile source files to object files
# -c flag compiles without linking
# @ suppresses command output
# $@ refers to the target name (the .o file)
# $< refers to the first prerequisite (the .c file)
$(BUILD)/obj/%.o: $(SRC)/%.c
	@mkdir -p $(BUILD)/obj
	$(CC) $(CFLAGS) -c -o $@ $<

# stage2: link object files into a final executable
# $^ refers to all prerequisites $(OBJS)
# $@ refers to the target name $(BINARY)
$(BINARY): $(OBJS)
	@mkdir -p $(BUILD)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

.PHONY: all clean

clean:
	@rm -rf $(BUILD)
