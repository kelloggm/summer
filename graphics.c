// @ Martin Kellogg, 2015
// graphics.c
// a simple graphics program
// based on the tutorial available at http://www.unix-manuals.com/tutorials/xlib/xlib.html on June 26, 2015; that tutorial is written by Manu Anand


// Hungarian glossary:
// dsp : display (from X11)
// scr : screen (from X11)
// dpt : depth (from X11)
// cnn : connection (from X11)
// wnd : window (from X11)
// x : from the X11 system
// swa : SetWindowAttributes (from X11)
// wms : Window MaSk (from X11)
// shn : SizeHints (from X11)


#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<stdio.h>
#include "hungarian.h"

//constants
#define xwBorder 2
#define xxXwnd 200
#define xyXwnd 200
#define xwXwnd 100
#define xhXwnd 100

//globals
Display *pxdsp;
int xdpt, xscr;

Window xwndFromXxXyXwXh(int xx, int xy, int xw, int xh, int f){
  XSetWindowAttributes xswa;
  unsigned long xwms;
  XSizeHints xshn;
  Window xwnd;
  
  // Set attributes
  xswa.border_pixel=BlackPixel(pxdsp, xscr);
  xswa.background_pixel = WhitePixel(pxdsp, xscr);
  xswa.override_redirect = ftrue;

  xwms = CWBackPixel|CWBorderPixel|CWOverrideRedirect;

  xwnd = XCreateWindow(pxdsp,
		       RootWindow(pxdsp, xscr),
		       xx,
		       xy,
		       xw,
		       xh,
		       xwBorder,
		       xdpt,
		       InputOutput,
		       CopyFromParent,
		       xwms,
		       &xswa);
  xshn.flags = PPosition|PSize;
  xshn.x = xx;
  xshn.y = xy;
  xshn.width = xw;
  xshn.height = xh;

  XSetNormalHints(pxdsp, xwnd, &xshn);
  
  XMapWindow(pxdsp, xwnd);
  XFlush(pxdsp);
  
  return xwnd;
}

int main(){
  Window xwnd;

  pxdsp = XOpenDisplay(NULL);
  if(pxdsp == NULL){
    fprintf(stderr, "Error: Given display cannot be opened");
    return 2;
  }
  xscr = DefaultScreen(pxdsp);
  xdpt = DefaultDepth(pxdsp, xscr);

  xwnd = xwndFromXxXyXwXh(xxXwnd, xyXwnd, xwXwnd, xhXwnd, 0);

  // We don't have anything interesting to do.
  sleep(10);
  
  XCloseDisplay(pxdsp);
}
