# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Target executable
TARGET = bin\main.exe

# Source files
UTILS = utils
UTILS_MENU = $(UTILS)/menu
UTILS_QUIZ_RELATED = $(UTILS)/quiz_related
SRCS = src/main.c $(UTILS_MENU)/print_header.c $(UTILS_MENU)/print_pause.c $(UTILS_QUIZ_RELATED)/timer.c

# Object directory
OBJDIR = obj

# Object files
OBJS = $(OBJDIR)/main.o $(patsubst utils/menu/%.c, $(OBJDIR)/%.o, $(filter utils/menu/%.c, $(SRCS))) $(patsubst utils/quiz_related/%.c, $(OBJDIR)/%.o, $(filter utils/quiz_related/%.c, $(SRCS)))

# Default target
all: $(TARGET)

# Rule to link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile main.c into main.o
$(OBJDIR)/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile other source files into object files
$(OBJDIR)/%.o: utils/menu/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile quiz_related source files into object files
$(OBJDIR)/%.o: utils/quiz_related/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up generated files
clean:
	del $(OBJDIR)\*.o $(TARGET)

# Phony targets
.PHONY: all clean
