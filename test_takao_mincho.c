#if 0
#!/bin/bash
src=$0
obj=${src%.*}
gcc -g -Wl,--no-as-needed `pkg-config --cflags --libs pango cairo pangocairo` -o $obj $src
$obj
exit
#endif

#if 0
#include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>

#include <cairo.h>
#include <pango/pangocairo.h>
#include <cairo-pdf.h>

typedef double real;

#define INCH  (2.54)
#define DPI   (72.0)
#define SCALE (DPI/INCH);

static void
set_font(
  PangoLayout *layout,
  char *family,
  real ab_size)
{
  PangoFontDescription* pfd = pango_font_description_new();
  pango_font_description_set_family(pfd, family);
  pango_font_description_set_absolute_size (pfd, (int)(ab_size * PANGO_SCALE));
  pango_layout_set_font_description (layout, pfd);
  pango_font_description_free (pfd);
}

static real
draw_string(
  cairo_t *cr,
  PangoLayout *layout,
  real x,
  real y,
  char *text)
{
  real yadv;
  cairo_set_source_rgba (cr, 0.0, 0.0, 0.0, 1.0);
  cairo_save (cr);
  /* alignment calculation done by pangocairo? */
  pango_layout_set_alignment (layout, PANGO_ALIGN_LEFT);
  pango_layout_set_text (layout, text, -1);
  {
    PangoLayoutIter *iter = pango_layout_get_iter(layout);
    int bline = pango_layout_iter_get_baseline(iter);
    PangoRectangle extents;
    pango_layout_iter_get_line_extents (iter, NULL, &extents);
    yadv = (double)(extents.height + bline) / PANGO_SCALE;
    cairo_move_to (cr, x, y - (double)bline / PANGO_SCALE);
    pango_layout_iter_free (iter);
  }
  /* does this hide bug #341481? */
  pango_cairo_update_context (cr, pango_layout_get_context (layout));
  pango_layout_context_changed (layout);

  pango_cairo_show_layout (cr, layout);
  cairo_restore (cr);
  return yadv;
}

extern int
main(
  int argc,
  char **argv)
{
  cairo_t *cr;
  cairo_surface_t *surface;
  PangoLayout *layout;
  real scale,width,height,size,x,y;
  int i;

  width = 21.0 * SCALE;
  height = 29.7 * SCALE;

  surface = cairo_pdf_surface_create("out.pdf",width,height);
  cairo_surface_set_fallback_resolution(surface,DPI,DPI);
  
  cr = cairo_create(surface);
  layout = pango_cairo_create_layout(cr);

  x = 3.0 * SCALE;
  y = 3.0 * SCALE;
  for(i=0; i<10; i++) {
    set_font(layout,"TakaoMincho",(i+1)*5);
    y += draw_string(cr,layout,x,y,"あいうえおかきくけこ") + 0.01 * SCALE;
  }

  cairo_show_page(cr);
  cairo_surface_finish(surface);
  return 0;
}
