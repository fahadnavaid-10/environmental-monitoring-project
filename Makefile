all: main

main: main.c alert.c data_processing.c
	gcc -o main main.c alert.c data_processing.c -I/usr/include/cjson -L/usr/lib/x86_64-linux-gnu -L/usr/local/lib -lcurl -lcjson
