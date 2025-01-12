# .PHONY := all build clean 
# ifeq ($(OS),Windows_NT)
# EXT := .exe
# else
# EXT := .out
# endif

# EXECNAME := temp_hum_test

# CC := gcc

# CFLAGS := -Wall -Wextra -Werror 

# SRCDIR := src
# INCDIR := inc
# OBJDIR := obj

# SRC := $(wildcard $(SRCDIR)/*.c)
# OBJ := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

# all: clean builddir $(EXECNAME)$(EXT)

# $(EXECNAME)$(EXT): $(OBJ)
# 	$(CC) -I$(INCDIR) $(OBJFILES) main.c -o $@

# builddir:
# ifeq ($(OS),Windows_NT)
# 	if not exist $(OBJDIR) mkdir $(OBJDIR)
# else
# 	if not [-d "$(OBJDIR)"]; then mkdir $(OBJDIR); fi
# endif


# $(OBJDIR)/%.o: $(SRCDIR)/%.c
# 	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# clean:
# ifeq ($(OS),Windows_NT)
# 	if exist $(OBJDIR) rmdir $(OBJDIR) /q /s
# 	if exist $(EXECNAME)$(EXT) del $(EXECNAME)$(EXT)
# else
# 	if [-e "./$(OBJDIR)/"]; 		 then rmdir -rf $(OBJDIR); fi
# 	if [-e "$(EXECNAME)"]; then rm $(EXECNAME); fi
# endif


# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinc

# Directories
SRC_DIR = src
INC_DIR = inc
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c) main.c
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))
TARGET = program

# Rules
all: $(BUILD_DIR) $(OBJ_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean