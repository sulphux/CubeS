all: CubeS CubeC

CubeS: serv.o
	gcc serv.o -o CubeS

CubeC: client.o
	gcc client.o -o CubeC

serv.o: serv/serwer.c
	gcc serv/serwer.c -o serv.o

client.o: client/client.c
	gcc client/client.c -o client.o

clean:
	rm -rf *.o

