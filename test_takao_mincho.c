#if 0
#!/bin/bash
src=$0
obj=${src%.*}
gcc -g -Wl,--no-as-needed `pkg-config --cflags --libs pango cairo pangocairo` -o $obj $src
$obj
exit
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
#define SCALE (DPI/INCH)

static void
set_font(
  PangoLayout *layout,
  char *family,
  real ab_size)
{
  PangoFontDescription* pfd = pango_font_description_new();

  pango_font_description_set_weight(pfd, PANGO_WEIGHT_NORMAL);
  pango_font_description_set_style(pfd, PANGO_STYLE_NORMAL);

  pango_font_description_set_family(pfd, family);
  pango_font_description_set_absolute_size (pfd, (int)(ab_size));
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

  pango_layout_set_alignment (layout, PANGO_ALIGN_LEFT);
  pango_layout_set_text (layout, text, -1);
  {
    PangoLayoutIter *iter = pango_layout_get_iter(layout);
    int bline = pango_layout_iter_get_baseline(iter);
    PangoRectangle extents;
    pango_layout_iter_get_line_extents (iter, NULL, &extents);
    yadv = (double)(extents.height + bline) / PANGO_SCALE;
    fprintf(stderr,"%lf\n",(double)(1.0 * extents.width / PANGO_SCALE));
    cairo_move_to (cr, x, y - (double)bline / PANGO_SCALE);
    pango_layout_iter_free (iter);
  }

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

  cairo_set_line_width(cr,1.0);
  cairo_set_dash(cr,NULL,0,0);
  cairo_set_source_rgba(cr,0.0,0.0,0.0,1.0);
  cairo_rectangle(cr, 0.95 * SCALE, 2.75 * SCALE, (17.3) * SCALE, (0.9) * SCALE);
  cairo_stroke(cr);

  x = 1.0 * SCALE;
  y = 3.4 * SCALE;

  for(i=0;i<20;i++) {
    set_font(layout,"TakaoMincho", 20000 - i * 200);
    y += draw_string(cr,layout,x,y,"あいうえおかきくけこさしすせそたちつてとなにぬねの");
  }

  cairo_show_page(cr);
  cairo_surface_finish(surface);
  return 0;
}
