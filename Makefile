CC      = i586-pc-msdosdjgpp-gcc
DOS     = dosbox
CFLAGS  = -std=gnu99 -Wall -Wextra -Os  \
          -Wno-unused-function  \
          -fno-stack-protector -Iinclude -g  # Add -g here
LDFLAGS =

OBJS = src/joystick.o src/rand.o src/kb.o src/time.o src/vga.o src/vga_font.o src/bullet.o src/particle.o src/ship.o src/powerup.o src/burn.o src/game.o src/speaker.o src/dosdef.o

.PHONY : all clean test

all: dosdef.exe

clean :
	$(RM) *.exe $(OBJS)

test : dosdef.exe
	$(DOS) $^

dosdef.exe : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
