graphics:
	gcc -o graphicsTest graphics.c -L/usr/X11R6/lib -lX11

clean:
	rm -f graphicsTest
	rm -f *~