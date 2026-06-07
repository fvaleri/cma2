CC = gcc
CFLAGS = -O2 -Wall -W -std=c99
LDFLAGS =
LDLIBS = -lrdkafka
SRC = src
BUILD = build

# find all .c file paths in the source directory
SRCS = $(wildcard $(SRC)/*.c)
# transform source file paths to target binaries
# example: src/hello.c becomes build/hello
TGTS = $(SRCS:$(SRC)/%.c=$(BUILD)/%)

all: $(TGTS)

# single-file build
# @ suppresses command output
# compile source files individually into binaries
# $@ refers to the target name (binary file)
# $< refers to the first prerequisite (the .c file)
$(BUILD)/%: $(SRC)/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

.PHONY: all clean

clean:
	@rm -rf $(BUILD)
