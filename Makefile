# Makefile for DOSDefender

# Compiler and flags
CC = i586-pc-msdosdjgpp-gcc
CFLAGS = -Wall -O2 -g -fcommon

# Source files
SRCS = src/defender.c src/game.c src/bullet.c src/burn.c src/joystick.c src/particle.c src/powerup.c src/ship.c src/speaker.c src/timemy.c src/vga.c src/vga_font.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HDRS = include/defender.h include/game.h include/bullet.h include/burn.h include/joystick.h include/particle.h include/powerup.h include/ship.h include/speaker.h include/timemy.h include/vga.h src/vga_font.h

# Executable name
EXE = defender.exe

# Allegro library
#ALLEGRO_LIB = -lalleg

# Build all
all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) -lalleg -lm -Wl,--allow-multiple-definition

# Compile source files to object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and executable
clean:
	rm -f src/*.o $(EXE) *.map
