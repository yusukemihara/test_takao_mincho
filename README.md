# test\_takao\_mincho

It seems that cairo or pango pdf some font rendereing have a problem with kerning on ubuntu 16.04.
I wrote small sample program.
see output.trusty.pdf and output.xenial.pdf.
Where is the difference from?

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
