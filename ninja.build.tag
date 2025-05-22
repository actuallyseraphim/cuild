cflags = -Wall -Wextra -O2
clibs =

rule cc
  command = gcc $cflags -MMD -MF $out.d -c $in -o $out
  depfile = $out.d

rule link
  command = gcc $clibs $in -o $out

rule install
  command = install -D $in $out
  description = Installing $in to $out

build install: phony /usr/bin/cuild
build /usr/bin/cuild: install cuild
