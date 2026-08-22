all: FSLib.so

FSLib.so: FSLib/main.c
	cc FSLib/main.c $(CFLAGS) -fPIC -shared -O2 -o $@
