/**
 *
 * Cube Server
 * Autor : Bogdan Cichy
 *
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>

#include "../lib/maps.h"
#include "../lib/konsola.h"
#include "../lib/defines.h"


//funkcja watku:
void *connection_handler(void *);

int main(int argc , char *argv[])
{
    zaladuj_mape();

    int socket_desc , client_sock , c , *new_sock;
    struct sockaddr_in server , client;

    //Stworz socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Nie mozna utworzyc socket'a\n");
    }
    puts("Socket stworzony!\n");

    //Przygotuj socket
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT );

    //Zlacz
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("Dowiazanie socketa nie powiodlo sie.");
        return 1;
    }
    puts("Dowiazanie stworzone.");

    //nasluchuj
    listen(socket_desc , 3);

    //Akceptuj nadchodzace polaczenia
    puts("Oczekuje na nadchodzace polaczenia...\n");
    c = sizeof(struct sockaddr_in);

    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Polaczenie zaakceptowane!");
        rysuj_mape();
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;

        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
        {
            perror("Nie moge utworzyc watku.");
            return 1;
        }

        //dolacz watek
        //pthread_join( sniffer_thread , NULL);
        puts("Watek dowiazany!");
    }

    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }

    return 0;
}

/*
 * Deklaracja watku
 * */
void *connection_handler(void *socket_desc)
{
    //Utworz deskryptor socket'u
    int sock = *(int*)socket_desc;
    int read_size;

    unsigned int dane[5]; // dane pozycji gracza
    dane[4] = NULL;
    char map_buff[BUFF_IO]; // bufor mapy do odczytania

    /// Czytaj dane polozenia
    while( (read_size = recv(sock , dane , sizeof(dane), 0)) > 0 )
    {

        mapa[dane[3]][dane[2]] = '.';
        mapa[dane[1]][dane[0]] = 'X';

        size_t i,j;

        size_t x = dane[0];
        size_t y = dane[1];

        x -= RES/2;
        y -= RES/2;


        for (j=0; j<RES; j++)
        {
            for(i=0; i<RES; i++)
            {
                if (y+j < 0 || x+i < 0 || y+j >= ROZ_Y || x+i >= ROZ_X)
                    map_buff[i+j*RES] = M00;
                else
                    map_buff[i+j*RES] = mapa[y + j][x + i];
            }
        }

        write(sock, map_buff,BUFF_IO);
        rysuj_mape();
        printf("\nx:%i y:%i\n", dane[0], dane[1]);
    }

    if(read_size == 0)
    {
        puts("Rozlaczono z klientem.");
        mapa[dane[1]][dane[0]] = '.';
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("Recv .. blad.");
    }

    //Wyczysc pamiec pod socket
    free(socket_desc);

    return 0;
}
