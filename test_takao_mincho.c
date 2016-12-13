#include	<config.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<signal.h>
#include    <sys/types.h>
#include    <sys/socket.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<sys/time.h>
#include	<sys/wait.h>

#include <errno.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <pango/pangocairo.h>
#include <cairo-pdf.h>

extern	int
main(
	int argc,
	char **argv)
{
	printf("init");
	return 0;
}
