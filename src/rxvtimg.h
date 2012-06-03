#ifndef IMG_H
#define IMG_H

#if defined HAVE_BG_PIXMAP && defined BG_IMAGE_FROM_FILE && defined ENABLE_TRANSPARENCY && defined HAVE_PIXBUF
  #define HAVE_IMG 1
#endif

#if HAVE_IMG

#include <X11/extensions/Xrender.h>

struct rxvt_img
{
  rxvt_screen *s;
  Pixmap pm;
  int w, h;
  XRenderPictFormat *format;
  bool shared; // true if we don't own it

  rxvt_img (rxvt_screen *screen, XRenderPictFormat *format, int width, int height);
  rxvt_img (rxvt_screen *screen, XRenderPictFormat *format, int width, int height, Pixmap pixmap);
  static rxvt_img *new_from_root (rxvt_screen *s); // get root pixmap
  static rxvt_img *new_from_file (rxvt_screen *s, const char *filename); // from pixbuf

  ~rxvt_img ();

  Pixmap steal ()
  {
    shared = true;
    return pm;
  }

  // inplace
  void fill (const rxvt_color &c);
  void blur (int rh, int rv);
  void brightness (double r, double g, double b, double a = 1.);
  void contrast (double r, double g, double b, double a = 1.);
  void render (GdkPixbuf *pixbuf, int src_x, int src_y, int width, int height, int dst_x, int dst_y);

  // copy
  rxvt_img *copy ();
  rxvt_img *scale (int new_width, int new_height);
  rxvt_img *transform (int new_width, int new_height, double matrix[16]);
};

#endif

#endif

