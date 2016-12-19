# test\_takao\_mincho

It seems that pango font rendereing have a problem with font size on ubuntu 16.04.
I wrote small sample program.
see output.(trusty|xenial).pdf.


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

* ubuntu 16.04 xenial - pango-1.38.1
* ubuntu 14.04 trusty - pango-1.36.3
