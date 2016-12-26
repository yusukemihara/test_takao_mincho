# test\_takao\_mincho

It seems that pango font rendereing have a problem with font size on ubuntu 16.10 and 16.04.
I wrote small sample program.
It render same japansese strings repeatedly,smaller and smaller.
In ubuntu 16.04 trusty(freetype-2.5.2),glyphs rendererd bit by bit smaller,
but in ubutun 16.10 yaketty, glyphs rendered same size at some lines.

see output.(trusty|yaketty).pdf.

What are the possible cause?
I should what to do?

## build and execute

```
$ ./test_takao_mincho.c
  -> out.pdf
```

## dependency

it needs follow deb packages.

* libcairo2-dev
* libpango1.0-dev
* libpangocairo-1.0-0
* fonts-takao

# pango-version

* ubuntu 16.10 yaketty - freetype-2.6.3
* ubuntu 14.04 trusty  - freetype-2.5.2
