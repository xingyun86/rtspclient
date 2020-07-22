I. Description (libregex-0_12.zip)

This is the GNU regular expression library 0.12 (libregex).
It is a part of GNU libc 2 and a lot of GNU programs need it
(e.g. GNU grep 2.4.2). However, all programs that need libregex
have their own version of libregex in their source code.
But why should anybody install this library separately?
Because you are now able to link this library dynamically into your
program (e.g. grep) if you compile it.

Note: For those people who never touch a compiler I have provided
      a binary distribution of this package (libregex-0_12-bin.zip)


II. Installation Requirements

- gcc (any version) and EMX runtime library (of course)

- GNU make (any version)



III. Installation instructions for libregex 0.12 (OS/2)

1. Run "make"

2. Copy the files regex.a, regex.lib, regex.dll wherever you want
   If you normally install your GNU tools into x:/my_gnu_programs
   I suggest you copy these files into x:/my_gnu_programs/lib.
   Add that directory to your LIBPATH and to your LIBRARY_PATH.



IV. Installation of regex 0.12 from the original GNU source

1. Get the newest version of glibc2 from ftp://ftp.gnu.org/gnu

2. You need only the files posix/regex.c and posix/regex.h from the tarball

3. Run "make"


--
Maintainer: Andreas Buening (andreas.buening@nexgo.de)

