cflags = -Wall -Wextra -O2 -ggdb
clibs = -lm

rule cc
  command = gcc $cflags -MMD -MF $out.d -c $in -o $out
  depfile = $out.d

rule link
  command = gcc $clibs $in -o $out
 