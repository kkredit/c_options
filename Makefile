# ------------------------------------------------
# Generic C Makefile
# ------------------------------------------------

TARGET   := prog
SRCDIR   := src
INCDIRS  := . options
OBJDIR   := build
BINDIR   := build

WARNINGS := \
	-Wall -Wextra -Wpedantic -Werror \
	-Wlogical-op -Wfloat-equal -Wcast-align \
	-Wparentheses -Wmissing-braces -Wconversion -Wsign-conversion \
	-Wwrite-strings -Wunknown-pragmas -Wunused-macros \
	-Wnested-externs -Wpointer-arith -Wswitch -Wredundant-decls \
	-Wreturn-type -Wshadow -Wunused -Wuninitialized \
	-Wdeclaration-after-statement -Wmissing-prototypes \
	-Wmissing-declarations -Wundef -fstrict-aliasing -Wstrict-aliasing=3 \
	-Wformat=2 -Wsuggest-attribute=pure -Wsuggest-attribute=const \
	-Wfatal-errors
	# -Waggregate-return -Wstrict-prototypes

OTHER_OPTS := -msign-return-address

CC       := gcc
CFLAGS   := -std=c99 $(WARNINGS) $(foreach dir,$(INCDIRS),-I$(dir))

LINKER   := gcc
LFLAGS   := $(WARNINGS) $(foreach dir,$(INCDIRS),-I$(dir))

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h) $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

.PHONY: all clean compile
default: all

all: $(BINDIR)/$(TARGET)

compile: $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(LINKER) $(OBJECTS) $(LFLAGS) -o $@

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
