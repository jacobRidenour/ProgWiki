ifneq (1,$(words $(CURDIR)))
$(error Containing path cannot contain whitespace: '$(CURDIR)')
endif
.RECIPEPREFIX = >
.PHONY: clean help
default: help

SHELL = /bin/bash

help: # Show help for each of the Makefile recipes.
> @grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done