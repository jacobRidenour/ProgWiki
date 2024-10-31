ifneq (1,$(words $(CURDIR)))
$(error Containing path cannot contain whitespace: '$(CURDIR)')
endif

SHELL := bash
.RECIPEPREFIX = >
.PHONY: clean help
default: help

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUT := a.out

CC := gcc
CFLAGS := -Wall -Werror -Wcast-align=strict -Wpedantic
INCLUDES := -I$(realpath ../../__tests)

# LDFLAGS := library/dirs
LDLIBS := -lm

demo: $(OBJS) # Create a Release (optimized) build
> $(CC) $(SRCS) $(CFLAGS) $(INCLUDES) $(LDLIBS) -o $(OUT)

debug: $(OBJS) # Create a Debug build
> $(CC) $(SRCS) $(CFLAGS) -g $(INCLUDES) $(LDLIBS) -o $(OUT)

%.o: %.c # Create object files from source files
> $(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean: # Remove intermediate and binary files
> $(RM) $(OBJS) $(OUT)

help: # Show help for each of the Makefile recipes.
> @grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done