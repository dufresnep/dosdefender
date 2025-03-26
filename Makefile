# Makefile for DOSDefender

CC = i586-pc-msdosdjgpp-gcc
CFLAGS = -Wall -O2 -g  -fcommon  # Restore -fcommon

LD = i586-pc-msdosdjgpp-gcc
LDFLAGS = -lalleg -Wl,--allow-multiple-definition # Add -Wl,--allow-multiple-definition

OBJS = src/defender.o src/game.o src/bullet.o src/burn.o src/joystick.o src/particle.o src/powerup.o src/ship.o src/speaker.o src/timemy.o src/vga.o src/vga_font.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

defender.exe: $(OBJS)
	$(LD) -o defender.exe $(OBJS) $(LDFLAGS)

clean:
	rm -f *.o defender.exe defender.map
