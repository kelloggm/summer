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
//#define xxXwnd 200
//#define xyXwnd 200
//#define xwXwnd 100
//#define xhXwnd 100
#define dxwBorder 100
#define dxhBorder 100

//error codes
#define xerr 2
#define xgcSuccess 1
#define xgcFailure 0

//globals
Display *pxdsp;
int xdpt, xscr;
GC xgc;
unsigned long xpxlWhite, xpxlBlack;


int xgcFromXwndPxgc(Window xwnd, GC *pxgc){
  XGCValues xgcv;
  *pxgc = XCreateGC(pxdsp, xwnd, (unsigned long) 0, &xgcv);
  if (*pxgc != 0){
    XSetForeground(pxdsp, *pxgc, xpxlWhite);
    XSetBackground(pxdsp, *pxgc, xpxlBlack);
    return xgcSuccess;
  }
  else{
    return xgcFailure;
  }
}

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

// MJK: Because of the way the preprocessor works, these can't take
// dxwBorder and dxhBorder as parameters

int xwFromWxDxwBorder(int wx){
  return (wx - (2 * dxwBorder));
}

int xhFromWyDxhBorder(int wy){
  return (wy - (2 * dxhBorder));
}

int main(){
  Window xwnd;
  int wx, wy;
  int xxXwnd, xyXwnd, xwXwnd, xhXwnd;

  pxdsp = XOpenDisplay(NULL);
  if(pxdsp == NULL){
    fprintf(stderr, "Error: Given display cannot be opened");
    return xerr;
  }
  xscr = DefaultScreen(pxdsp);
  xdpt = DefaultDepth(pxdsp, xscr);
  xpxlWhite = WhitePixel(pxdsp, xscr);
  xpxlBlack = BlackPixel(pxdsp, xscr);

  wx = DisplayWidth(pxdsp, xscr);
  wy = DisplayHeight(pxdsp, xscr);

  xwXwnd = xwFromWxDxwBorder(wx);
  xhXwnd = xhFromWyDxhBorder(wy);
  xxXwnd = dxwBorder;
  xyXwnd = dxhBorder;

  xwnd = xwndFromXxXyXwXh(xxXwnd, xyXwnd, xwXwnd, xhXwnd, 0);

  if (xgcFromXwndPxgc(xwnd, &xgc) == xgcFailure){
    fprintf(stderr, "Error: X cannot create gc");
    return xerr;
  }

  // We don't have anything interesting to do.
  sleep(10);
  
  XCloseDisplay(pxdsp);
}
