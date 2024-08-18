ifneq (1,$(words $(CURDIR)))
$(error Containing path cannot contain whitespace: '$(CURDIR)')
endif

.RECIPEPREFIX = >
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables --no-builtin-rules

SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c 
.ONESHELL:


.PHONY: clean help
default: help

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUT := a.out

CC := gcc
CFLAGS := -Wall -Werror -Wcast-align=strict -Wpedantic
# LDFLAGS := library/dirs
LDLIBS := -lm


debug: $(OBJS) # Debug (with symbols) build
> $(CC) $(SRCS) $(CFLAGS) $(LDLIBS) -o $(OUT)

release: $(OBJS) # Release (optimized) build
> $(CC) $(SRCS) $(CFLAGS) $(LDLIBS) -o $(OUT)

help: # Show help for each of the Makefile recipes.
> @grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done