#IMPORTANT: This must be very concise. Any variation will be rejected.
# Makefile for DJGPP Dosdefender

# Compiler and linker settings
CC = i586-pc-msdosdjgpp-gcc
#CFLAGS = -Wall -O1 -g -Iinclude -fcommon
CFLAGS = -O2 -g -Iinclude -fcommon
LDFLAGS = -static -lalleg -lalld -lallp -m32 -L/usr/local/djgpp/i586-pc-msdosdjgpp/lib -Wl,--allow-multiple-definition

# Source files
SRC = src/defender.c src/game.c src/bullet.c src/burn.c src/joystick.c src/particle.c src/powerup.c src/ship.c src/speaker.c src/time.c src/vga.c src/vga_font.c
OBJ = $(SRC:.c=.o)
EXE = defender.exe

# Rule to create the executable
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LDFLAGS)

# Rule to create object files from C source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Phony targets
.PHONY: all clean

all: $(EXE)

clean:
	rm -f $(OBJ) $(EXE) defender.map
