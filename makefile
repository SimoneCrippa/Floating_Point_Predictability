CC=gcc	#for ARM arm-linux-gnueabi-gcc
SRC_DIR = $(shell pwd)
BUILD_DIR = $(shell pwd)/builds
RESULTS_DIR = $(shell pwd)/results
CFLAGS=	#for ARM add -static -march=armv8-a
SOURCES=$(shell find $(SRC_DIR)/ -name "*_bench_*.c")
EXECUTABLES=$(SOURCES:.c=)

.SUFFIXES: .c

all: $(SOURCES) $(EXECUTABLES)

$(EXECUTABLES): $(SOURCES)
	$(CC) $(CFLAGS) $(@:=.c) -o $(BUILD_DIR)/$(notdir $@) fixed_op_64bit.c

init:
	mkdir results
	mkdir builds

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(RESULTS_DIR)

run: 
	cd $(RESULTS_DIR) && for x in $(shell find $(BUILD_DIR)/ -name "*_bench_*"); do $$x; done

