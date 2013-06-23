#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<time.h>

#include "../lib/konsola.h"
#include "../lib/defines.h"

struct pozycja
{
    unsigned int x;
    unsigned int y;
};

struct play
{
    struct pozycja poz;
    struct pozycja poprzednia;
    char wyglad;
} player;

void InicjujPlayera()
{
    srand(time(NULL));
    //player.poz.x = abs((rand()*ROZ_X)/1);
    //player.poz.y = abs((rand()*ROZ_Y)/1);
    player.poz.x = 6;
    player.poz.y = 3;
    player.wyglad = 'X';
}

unsigned int pobierzX()
{
    return player.poz.x;
}

unsigned int pobierzY()
{
    return player.poz.y;
}

unsigned int poprzedniX()
{
    return player.poprzednia.x;
}

unsigned int poprzedniY()
{
    return player.poprzednia.y;
}

int main(int argc , char *argv[])
{
    InicjujPlayera();
    initTermios(0);

    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];

    ///Stworz socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Nie mozna utworzyc socket'a\n");
    }

    puts("Socket stworzony\n");

    server.sin_addr.s_addr = inet_addr(ADDRESS);
    server.sin_family = AF_INET;
    server.sin_port = htons( PORT );

    ///Polacz z serwerem
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Polaczenie nie udane. Error");
        return 1;
    }

    puts("Polaczono!\n");

    unsigned int dane[5];
    char odpowiedz[BUFF_IO];
    char wcisnety;

    size_t i;
    for(i=0; i<BUFF_IO; i++)
    {
        odpowiedz[i] = NULL;
    }

    system("reset");

    ///Utrzymuj polaczenie z serwerem
    while(1)
    {
        wcisnety = getch();

        player.poprzednia.x = player.poz.x;
        player.poprzednia.y = player.poz.y;

        /// UP.....65
        /// DOWN...66
        /// LEFT...68
        /// RIGHT..67

        switch (wcisnety)
        {
        case 65 :
            if (player.poz.y != 0)
                player.poz.y--;
            break;
        case 66 :
            if (player.poz.y < ROZ_Y-1)
                player.poz.y++;
            break;
        case 68 :
            if (player.poz.x > 0)
                player.poz.x--;
            break;
        case 67 :
            if (player.poz.x < ROZ_X-1)
                player.poz.x++;
            break;
        case 'q' :
        case 'Q' :

            close(sock);
            system("reset");
            exit(0);
            break;
        }

        dane[0] = pobierzX();
        dane[1] = pobierzY();
        dane[2] = poprzedniX();
        dane[3] = poprzedniY();
        dane[4] = NULL;


        ///Wyslij dane
        if( send(sock , dane , sizeof(dane) , 0) < 0)
        {
            puts("Problem z polaczeniem.");
            return 1;
        }

        ///Otrzymaj odpowiedz z serwera
        if( recv(sock , odpowiedz, BUFF_IO, 0) < 0)
        {
            puts("Brak odpowiedzi z serwera\n");
            break;
        }

        clearScreen();
        unsigned int i = 0;
        while(i < BUFF_IO)
        {
            putchar(odpowiedz[i-1]);
            if (i % RES == 0)
                putchar('\n');
            i++;
        }

        //printf("\n%i\n",(int)wcisnety);
        ///debug klawiszy

        printf("\n\n\nWcisnij \'Q\' by wyjsc.\n");
    }

    close(sock);
    return 0;
}
