# DOS Defender

Hi, I modified this a lot, and now I would be surprise if it works.
It was reorganised (lots of code removed) in a way to compile with
a real DOS gcc (although I compile with a linux to DJGPP compiler).

The structure is now much more classic.
The result is dosdef.exe (copied to bin directory).
And that needs DPMI (does not works in DOSBOX).

Here is a youtube video about this game:
https://www.youtube.com/watch?v=6UjuFnZYkG4

DOS Defender is an x86 real mode DOS game for [Ludum Dare #31][ld]
(December, 2014). Since few DOS machines still exist, the target
platform is actually [DOSBox][db], though it should work to some
extent on any DOS system. The game *can* be played with a mouse but
it's **intended to be played with a joystick/gamepad**.

![](http://i.imgur.com/B58ogsG.gif)

![](http://i.imgur.com/YQ82yLk.png)
![](http://i.imgur.com/IWJvurZ.png)

* [How to build DOS COM files with GCC][blog]
* [Random DOS Game Show Special: DOS Defender (2014)][video]
* [The New Retro Show plays DOS Defender][retro]

## Playing

Just point DOSBox at the COM binary.

    $ dosbox DOSDEF.COM

There are no external assets, so mounting isn't necessary.

## Building

All you need is a GCC compiler that can target i386. In theory, it
doesn't matter if it's for Linux, Windows, etc., nor is there a need
for something like DJGPP. The compiled code will be packaged as a COM
file using a linker script (e.g. `--oformat=binary`). Unfortunately,
there's a long-standing bug in MinGW that prevents this from working
correctly without `objdump`.

The final game is a 10kB executable. To run, all it needs is 64kB of
RAM and 64kB of video memory. With some tweaking, it could even run
without a need for any OS.

DOS Defender is written in GCC's dialect of C and probably can't be
built with any other compiler. The host platform is treated like an
embedded system, so there's no intention of actually building the game
from within DOS itself. Compilation is done as a single translation
unit to allow the optimizer full reign in minimizing the code size
(COM files are limited to 64kB).


[blog]: https://nullprogram.com/blog/2014/12/09/
[db]: http://www.dosbox.com/
[ld]: http://ludumdare.com/compo/2014/12/03/welcome-to-ludum-dare-31/
[video]: https://www.youtube.com/watch?v=6UjuFnZYkG4
[retro]: https://www.youtube.com/watch?v=eWcKTXAeljo&t=9m36s
