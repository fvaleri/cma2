CC = gcc
CFLAGS = -O2 -Wall -W -std=c99
LDFLAGS =
LDLIBS = -lrdkafka
SRC = src
BUILD = build

# find all .c file paths in the source directory
SRCS = $(wildcard $(SRC)/*.c)
# transform source file paths to target binaries
# example: src/hello.c becomes hello
TGTS = $(SRCS:$(SRC)/%.c=%)

all: setup $(TGTS)

setup:
	mkdir -p $(BUILD)/bin

# compile source files individually into binaries
# % is a wildcard that matches any target name
# $@ refers to the target name (binary file)
# $< refers to the first prerequisite (the .c file)
%: $(SRC)/%.c | setup
	$(CC) $(CFLAGS) -o $(BUILD)/bin/$@ $< $(LDFLAGS) $(LDLIBS)

.PHONY: all clean

clean:
	rm -rf $(BUILD)
