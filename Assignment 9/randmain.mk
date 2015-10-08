CC=gcc

all: randlibhw.so randlibsw.so randmain

randlibhw.so: randlibhw.c
	$(CC) randlibhw.c -shared -fPIC -o randlibhw.so

randlibsw.so: randlibsw.c
	$(CC) randlibsw.c -shared -fPIC -o randlibsw.so

randmain: randmain.c
	$(CC) -c randcpuid.c
	$(CC) -c randmain.c
	$(CC) randmain.o randcpuid.o -ldl -mrdrnd -Wl,-rpath=. -o randmain
