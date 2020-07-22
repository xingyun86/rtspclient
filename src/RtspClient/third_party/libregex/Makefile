all:
	@echo Note: ignore the warning about "implicit declaration of function `free'"!
	gcc -c regex.c -Wall -I. -O3 -s -Zmt
	@echo LIBRARY REGEX INITINSTANCE TERMINSTANCE > regex.def
	@echo DESCRIPTION 'GNU regular expression library 0.12' >> regex.def
	@echo STACKSIZE 32768 >> regex.def
	@echo EXPORTS >> regex.def
	emxexp regex.o >> regex.def
	ar rc regex.a regex.o
	emxomf regex.o
	emximp -o regex.lib regex.def
	gcc -o regex.dll regex.def regex.obj -Zdll -Zomf -Zcrtdll -Zlinker /exepack:2 -s -Zmt


clean:
	if exist regex.o del regex.o
	if exist regex.obj del regex.obj
	if exist regex.def del regex.def


distclean: clean
	if exist regex.a del regex.a
	if exist regex.lib del regex.lib
	if exist regex.dll del regex.dll

