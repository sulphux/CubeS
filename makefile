all: CubeS CubeC

CubeS: serv.o
	gcc serv.o -o CubeS

CubeC: client.o
	gcc client.o -o CubeC

serv.o: serv/serwer.c
	gcc serv/serwer.c -lpthread -o serv.o

client.o: client/client.c
	gcc client/client.c -lpthread -o client.o

clean:
	rm -rf serv.o client.o

